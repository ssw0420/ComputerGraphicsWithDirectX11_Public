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
		BasicPixelConstantData _basicPixelConstantData;

		NormalVertexConstantData _normalVertexConstantData;
		bool _bDrawNormalsDirtyFlag = true;
		bool _bDrawNormals = false;

	private:
		std::vector<shared_ptr<Mesh>> _meshes;

		ComPtr<ID3D11VertexShader> _basicVertexShader;
		ComPtr<ID3D11PixelShader> _basicPixelShader;
		ComPtr<ID3D11InputLayout> _basicInputLayout;

		ComPtr<ID3D11Buffer> _vertexConstantBuffer;
		ComPtr<ID3D11Buffer> _pixelConstantBuffer;

		ComPtr<ID3D11VertexShader> _normalVertexShader;
		ComPtr<ID3D11PixelShader> _normalPixelShader;

		shared_ptr<Mesh> _normalLines;

		ComPtr<ID3D11Buffer> _normalVertexConstantBuffer;

		ComPtr<ID3D11SamplerState> _samplerState;
	};
}