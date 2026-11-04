#include "BasicMeshGroup.h"

namespace ssw
{
	void BasicMeshGroup::Initialize(ComPtr<ID3D11Device>& device, const std::vector<MeshData>& meshes)
	{
		D3D11Utils::CreateConstantBuffer(device, _basicVertexConstantData,
			_vertexConstantBuffer);

		for (const auto& meshData : meshes)
		{
			auto newMesh = std::make_shared<Mesh>();
			D3D11Utils::CreateVertexBuffer(device, meshData.vertices, newMesh->_vertexBuffer);
			newMesh->_indexCount = UINT(meshData.indices.size());
			
			D3D11Utils::CreateIndexBuffer(device, meshData.indices, newMesh->_indexBuffer);

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
	}

	void BasicMeshGroup::UpdateConstantBuffers(ComPtr<ID3D11Device>& device, ComPtr<ID3D11DeviceContext>& context)
	{
		D3D11Utils::UpdateBuffer(device, context, _basicVertexConstantData, _vertexConstantBuffer);
	}

	void BasicMeshGroup::Render(ComPtr<ID3D11DeviceContext>& context)
	{
		context->VSSetShader(_basicVertexShader.Get(), nullptr, 0);
		context->PSSetShader(_basicPixelShader.Get(), nullptr, 0);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		for (const auto& mesh : _meshes)
		{
			context->IASetInputLayout(_basicInputLayout.Get());
			context->IASetVertexBuffers(0, 1, mesh->_vertexBuffer.GetAddressOf(), &stride, &offset);
			context->IASetIndexBuffer(mesh->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			context->VSSetConstantBuffers(0, 1, _vertexConstantBuffer.GetAddressOf());

			context->DrawIndexed(mesh->_indexCount, 0, 0);
		}
	}
}