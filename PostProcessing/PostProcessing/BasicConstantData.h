#pragma once

#include <directxtk/SimpleMath.h>

#include "Light.h"
#include "Material.h"

namespace ssw
{
	using DirectX::SimpleMath::Matrix;

	struct BasicVertexConstantData
	{
		Matrix model;
		Matrix view;
		Matrix projection;
		Matrix invTranspose;
	};

	// 컴파일 타임에 검사
	static_assert((sizeof(BasicVertexConstantData) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");

	struct NormalVertexConstantData
	{
		float scale = 0.1f;
		float dummy[3];
	};

	static_assert((sizeof(NormalVertexConstantData) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");

	struct BasicPixelConstantData
	{
		Vector3 eyeWorld;
		int useTexture = 1;
		Material material;
		Light lights[MAX_LIGHTS];
	};

	static_assert((sizeof(BasicPixelConstantData) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");
}