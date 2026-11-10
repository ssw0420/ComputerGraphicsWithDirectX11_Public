#include "BasicMeshGroup.h"

namespace ssw
{
	void BasicMeshGroup::Initialize(ComPtr<ID3D11Device>& device, const std::vector<MeshData>& meshes)
	{
		D3D11Utils::CreateConstantBuffer(device, _basicVertexConstantData,
			_vertexConstantBuffer);

		D3D11Utils::CreateConstantBuffer(device, _basicPixelConstantData,
			_pixelConstantBuffer);

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV= D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		device->CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());

		for (const auto& meshData : meshes)
		{
			auto newMesh = std::make_shared<Mesh>();
			D3D11Utils::CreateVertexBuffer(device, meshData.vertices, newMesh->_vertexBuffer);
			newMesh->_indexCount = UINT(meshData.indices.size());
			
			D3D11Utils::CreateIndexBuffer(device, meshData.indices, newMesh->_indexBuffer);

			if (!meshData.textureFileName.empty())
			{
				std::cout << meshData.textureFileName << std::endl;
				D3D11Utils::CreateTexture(device, meshData.textureFileName, newMesh->_texture, newMesh->_textureResourceView);
			}

			this->_meshes.push_back(newMesh);
		}

		vector<D3D11_INPUT_ELEMENT_DESC> basicInputElements =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		D3D11Utils::CreateVertexShaderAndInputLayout(device,
			L"BasicVS.hlsl",
			basicInputElements,
			_basicVertexShader,
			_basicInputLayout);

		D3D11Utils::CreatePixelShader(device,
			L"BasicPS.hlsl",
			_basicPixelShader);

		_normalLines = std::make_shared<Mesh>();

		std::vector<Vertex> normalVertices;
		std::vector<uint32_t> normalIndices;

		size_t offset = 0;

		for (const auto& meshData : meshes)
		{
			for (size_t i = 0; i < meshData.vertices.size(); ++i)
			{
				auto v = meshData.vertices[i];
				
				v.texcoord.x = 0.0f;
				normalVertices.push_back(v);

				v.texcoord.x = 1.0f;
				normalVertices.push_back(v);

				normalIndices.push_back(uint32_t(2 * (i + offset)));
				normalIndices.push_back(uint32_t(2 * (i + offset) + 1));
			}
			offset += meshData.vertices.size();
		}

		D3D11Utils::CreateVertexBuffer(device, normalVertices, _normalLines->_vertexBuffer);
		_normalLines->_indexCount = UINT(normalIndices.size());

		D3D11Utils::CreateIndexBuffer(device, normalIndices, _normalLines->_indexBuffer);

		D3D11Utils::CreateVertexShaderAndInputLayout(device,
			L"NormalVS.hlsl",
			basicInputElements,
			_normalVertexShader,
			_basicInputLayout);

		D3D11Utils::CreatePixelShader(device,
			L"NormalPS.hlsl",
			_normalPixelShader);

		D3D11Utils::CreateConstantBuffer(device, _normalVertexConstantData, _normalVertexConstantBuffer);
	}

	void BasicMeshGroup::UpdateConstantBuffers(ComPtr<ID3D11Device>& device, ComPtr<ID3D11DeviceContext>& context)
	{
		D3D11Utils::UpdateBuffer(device, context, _basicVertexConstantData, _vertexConstantBuffer);
		D3D11Utils::UpdateBuffer(device, context, _basicPixelConstantData, _pixelConstantBuffer);
		
		if (_bDrawNormals && _bDrawNormalsDirtyFlag)
		{
			D3D11Utils::UpdateBuffer(device, context, _normalVertexConstantData, _normalVertexConstantBuffer);
			_bDrawNormalsDirtyFlag = false;
		}
	}

	void BasicMeshGroup::Render(ComPtr<ID3D11DeviceContext>& context)
	{
		context->VSSetShader(_basicVertexShader.Get(), nullptr, 0);
		context->PSSetShader(_basicPixelShader.Get(), nullptr, 0);
		context->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		for (const auto& mesh : _meshes)
		{
			context->IASetInputLayout(_basicInputLayout.Get());
			context->IASetVertexBuffers(0, 1, mesh->_vertexBuffer.GetAddressOf(), &stride, &offset);
			context->IASetIndexBuffer(mesh->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			context->VSSetConstantBuffers(0, 1, _vertexConstantBuffer.GetAddressOf());
			
			context->PSSetShaderResources(0, 1, mesh->_textureResourceView.GetAddressOf());

			context->PSSetConstantBuffers(0, 1, _pixelConstantBuffer.GetAddressOf());

			context->DrawIndexed(mesh->_indexCount, 0, 0);
		}

		if (_bDrawNormals)
		{
			context->VSSetShader(_normalVertexShader.Get(), nullptr, 0);
			context->PSSetShader(_normalPixelShader.Get(), nullptr, 0);

			context->IASetInputLayout(_basicInputLayout.Get());
			context->IASetVertexBuffers(0, 1, _normalLines->_vertexBuffer.GetAddressOf(), &stride, &offset);
			context->IASetIndexBuffer(_normalLines->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		
			ID3D11Buffer* pptr[2] = { _vertexConstantBuffer.Get(), _normalVertexConstantBuffer.Get() };
			context->VSSetConstantBuffers(0, 2, pptr);

			context->DrawIndexed(_normalLines->_indexCount, 0, 0);
		}
	}
}