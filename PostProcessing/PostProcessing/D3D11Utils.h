#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <wrl.h> // ComPtr

namespace ssw
{
	using Microsoft::WRL::ComPtr;
	using std::shared_ptr;
	using std::vector;
	using std::wstring;

	class D3D11Utils
	{
	public:
		static void CreateVertexShaderAndInputLayout(ComPtr<ID3D11Device>& device,
			const wstring& filename,
			const vector<D3D11_INPUT_ELEMENT_DESC>& inputElements,
			ComPtr<ID3D11VertexShader>& vertexShader,
			ComPtr<ID3D11InputLayout>& inputLayout);

		static void CreateIndexBuffer(ComPtr<ID3D11Device>& device,
			const vector<uint32_t>& indices,
			ComPtr<ID3D11Buffer>& indexBuffer);

		static void CreatePixelShader(ComPtr<ID3D11Device>& device,
			const wstring& filename,
			ComPtr<ID3D11PixelShader>& pixelShader);

		template <typename T_CONSTANT>
		static void CreateConstantBuffer(ComPtr<ID3D11Device>& device,
			const T_CONSTANT& constantBufferData,
			ComPtr<ID3D11Buffer>& constantBuffer)
		{
			D3D11_BUFFER_DESC cbDesc;
			cbDesc.ByteWidth = sizeof(constantBufferData);
			cbDesc.Usage = D3D11_USAGE_DYNAMIC;
			cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbDesc.MiscFlags = 0;
			cbDesc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem = &constantBufferData;
			initData.SysMemPitch = 0;
			initData.SysMemSlicePitch = 0;

			HRESULT hr = device->CreateBuffer(&cbDesc, &initData, constantBuffer.GetAddressOf());
			if (FAILED(hr))
			{
				std::cout << "CreateConstantBuffer() FAILED" << std::hex << hr << std::dec << std::endl;
			}
		}

		template <typename T_VERTEX>
		static void CreateVertexBuffer(ComPtr<ID3D11Device>& device,
			const vector<T_VERTEX>& vertices,
			ComPtr<ID3D11Buffer>& vertexBuffer)
		{
			D3D11_BUFFER_DESC vbDesc = {};
			vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
			vbDesc.ByteWidth = UINT(sizeof(T_VERTEX) * vertices.size());
			vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbDesc.CPUAccessFlags = 0;
			vbDesc.StructureByteStride = sizeof(T_VERTEX);

			D3D11_SUBRESOURCE_DATA vbData = {};
			vbData.pSysMem = vertices.data();
			vbData.SysMemPitch = 0;
			vbData.SysMemSlicePitch = 0;

			const HRESULT hr = device->CreateBuffer(&vbDesc, &vbData, vertexBuffer.GetAddressOf());
			if (FAILED(hr))
			{
				std::cout << "CreateVertexBuffer() FAILED " << std::hex << hr << std::dec << std::endl;
			};
		}

		template <typename T_DATA>
		static void UpdateBuffer(ComPtr<ID3D11Device>& device,
			ComPtr<ID3D11DeviceContext>& context,
			const T_DATA& bufferData,
			ComPtr<ID3D11Buffer>& buffer)
		{

			if (!buffer) {
				std::cout << "UpdateBuffer() buffer was NOT initialized."
					<< std::endl;
			}

			D3D11_MAPPED_SUBRESOURCE ms;
			context->Map(buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, &bufferData, sizeof(bufferData));
			context->Unmap(buffer.Get(), NULL);
		}
	};
}