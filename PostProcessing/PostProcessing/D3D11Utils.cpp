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
		HRESULT hr = D3DCompileFromFile(L"BasicVS.hlsl",
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

		HRESULT hr = D3DCompileFromFile(L"BasicPS.hlsl",
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

}