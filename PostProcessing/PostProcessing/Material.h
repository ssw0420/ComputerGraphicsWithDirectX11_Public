#pragma once

#include <directxtk/SimpleMath.h>

namespace ssw
{
	using DirectX::SimpleMath::Vector3;

	struct Material
	{
		Vector3 ambient = Vector3(0.0f);
		float shininess = 0.01f;
		Vector3 diffuse = Vector3(0.0f);
		float dummy1;
		Vector3 specular = Vector3(1.0f);
		float dummy2;
	};
}