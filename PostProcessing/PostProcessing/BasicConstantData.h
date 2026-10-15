#pragma once

#include <directxtk/SimpleMath.h>

namespace ssw
{
	using DirectX::SimpleMath::Matrix;

	struct BasicVertexConstantData
	{
		Matrix model;
		Matrix view;
		Matrix projection;
	};

	// 컴파일 타임에 검사
	static_assert((sizeof(BasicVertexConstantData) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");
}