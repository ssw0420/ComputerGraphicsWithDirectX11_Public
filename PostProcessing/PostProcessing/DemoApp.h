#pragma once

#include <algorithm>
#include <iostream>
#include <memory>

#include "Application.h"
#include "BasicMeshGroup.h"

namespace ssw
{
	using DirectX::SimpleMath::Vector3;

	class DemoApp : public Application
	{
	public:
		DemoApp();

		virtual bool Initialize() override;
		virtual void Render() override;
		virtual void Update(float dt) override;

	private:
		//Mesh _box;
		//Mesh _mesh;

		//ComPtr<ID3D11VertexShader> _vertexShader;
		//ComPtr<ID3D11PixelShader> _pixelShader;
		//ComPtr<ID3D11InputLayout> _inputLayout;

		BasicMeshGroup _meshGroupSphere;

		// 물체 원근, 위치, 회전, 크기
		bool _usePerspectiveProjection = true;
		Vector3 _modelTranslation = Vector3(0.0f);
		Vector3 _modelRotation = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 _modelScaling = Vector3(1.8f);

		// 시야각 및 거리
		Vector3 _viewRot = Vector3(-0.1f, 0.0f, 0.0f);
		float _projFovAngleY = 70.0f;
		float _nearZ = 0.01f;
		float _farZ = 100.0f;
	};
}