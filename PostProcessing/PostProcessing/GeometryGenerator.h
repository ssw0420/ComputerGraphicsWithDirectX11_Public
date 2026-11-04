#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>
#include <string>

#include "MeshData.h"

namespace ssw
{
	class GeometryGenerator
	{
	public:
		static MeshData MakeBox(const float scale = 1.0f);
		static MeshData MakeCylinder(const float bottomRadius, const float topRadius, float height, int numSlices);
		static MeshData MakeSphere(const float radius, const int numSlices, const int numStacks);
	};
}