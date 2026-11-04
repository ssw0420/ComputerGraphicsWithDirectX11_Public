#pragma once

#include "BasicConstantData.h"
#include "Mesh.h"
#include "MeshData.h"
#include "D3D11Utils.h"

namespace ssw
{
	class BasicMeshGroup
	{
	public:
		void Initialize(ComPtr<ID3D11Device>& device, const std::vector<MeshData>& meshes);

		void UpdateConstantBuffers(ComPtr<ID3D11Device>& device, ComPtr<ID3D11DeviceContext>& context);

		void Render(ComPtr<ID3D11DeviceContext>& context);

	public:
		BasicVertexConstantData _basicVertexConstantData;

	private:
		std::vector<shared_ptr<Mesh>> _meshes;

		ComPtr<ID3D11VertexShader> _basicVertexShader;
		ComPtr<ID3D11PixelShader> _basicPixelShader;
		ComPtr<ID3D11InputLayout> _basicInputLayout;

		ComPtr<ID3D11Buffer> _vertexConstantBuffer;
	};
}