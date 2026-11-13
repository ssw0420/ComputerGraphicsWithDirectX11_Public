#include "D3D11Utils.h"

#include <dxgi.h>
#include <dxgi1_4.h>
#include <iostream>
#include <directxtk/DDSTextureLoader.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "d3dcompiler.lib")

namespace ssw
{
	using namespace std;
	using namespace DirectX;

	void CheckResult(HRESULT hr, ID3DBlob* errorBlob)
	{
		if (FAILED(hr))
		{
			if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			{
				cout << "File NOT Found" << endl;
			}

			if (errorBlob)
			{
				cout << "Shader compile ERROR\n" << (char*)errorBlob->GetBufferPointer() << endl;
			}
		}
	}

	void D3D11Utils::CreateVertexShaderAndInputLayout(ComPtr<ID3D11Device>& device, const wstring& filename, const vector<D3D11_INPUT_ELEMENT_DESC>& inputElements, ComPtr<ID3D11VertexShader>& vertexShader, ComPtr<ID3D11InputLayout>& inputLayout)
	{
		ComPtr<ID3DBlob> vsBlob;
		ComPtr<ID3DBlob> errorBlob;

		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		HRESULT hr = D3DCompileFromFile(filename.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"vs_5_0",
			compileFlags,
			0,
			&vsBlob,
			&errorBlob);

		CheckResult(hr, errorBlob.Get());

		device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
	
		device->CreateInputLayout(inputElements.data(),
			UINT(inputElements.size()),
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&inputLayout);
	}

	void D3D11Utils::CreatePixelShader(ComPtr<ID3D11Device>& device, const wstring& filename, ComPtr<ID3D11PixelShader>& pixelShader)
	{
		ComPtr<ID3DBlob> psBlob;
		ComPtr<ID3DBlob> errorBlob;

		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT hr = D3DCompileFromFile(filename.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"ps_5_0",
			compileFlags,
			0,
			&psBlob,
			&errorBlob);

		CheckResult(hr, errorBlob.Get());

		device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader);
	}

	void D3D11Utils::CreateIndexBuffer(ComPtr<ID3D11Device>& device, const vector<uint32_t>& indices, ComPtr<ID3D11Buffer>& indexBuffer)
	{
		D3D11_BUFFER_DESC ibDesc = {};
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
		ibDesc.ByteWidth = UINT(sizeof(uint32_t) * indices.size());
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.StructureByteStride = sizeof(uint32_t);

		D3D11_SUBRESOURCE_DATA ibData = {};
		ibData.pSysMem = indices.data();
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		device->CreateBuffer(&ibDesc, &ibData, indexBuffer.GetAddressOf());
	}

	void D3D11Utils::CreateTexture(ComPtr<ID3D11Device>& device, const std::string filename, ComPtr<ID3D11Texture2D>& texture, ComPtr<ID3D11ShaderResourceView>& textureResourceView)
	{
		int width = 0;
		int height = 0;
		int channels = 0; // 이미지의 픽셀 하나에 들어있는 색 개수 - R, G, B
		unsigned char* loadedPixels = stbi_load(filename.c_str(), &width, &height, &channels, 0);

		if (!loadedPixels)
		{
			cout << "stbi_load() FAILED: " << filename << endl;
			cout << stbi_failure_reason() << endl;
			return;
		}

		// RGB 3바이트 -> RGBA 4바이트 (DXGI에 24비트 RGB 형식이 없음)
		vector<uint8_t> rgbaPixels;
		rgbaPixels.resize(width * height * 4);
		for (size_t pixelIndex = 0; pixelIndex < width * height; ++pixelIndex)
		{
			size_t srcStart = pixelIndex * channels;
			size_t destStart = pixelIndex * 4; // RGBA
			
			for (size_t channelIndex = 0; channelIndex < 3; ++channelIndex)
			{
				rgbaPixels[destStart + channelIndex] = loadedPixels[srcStart + channelIndex];
			}
			// 채널이 3개인 경우 A 부분에 매 반복마다 255를 넣음
			rgbaPixels[destStart + 3] = (channels == 4) ? loadedPixels[srcStart + 3] : 255;
			//rgbaPixels[destStart + 3] = 255;
		}

		stbi_image_free(loadedPixels);

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = rgbaPixels.data();
		initData.SysMemPitch = textureDesc.Width * sizeof(uint8_t) * 4;

		device->CreateTexture2D(&textureDesc, &initData, texture.GetAddressOf());

		device->CreateShaderResourceView(texture.Get(), nullptr, textureResourceView.GetAddressOf());
	}
}