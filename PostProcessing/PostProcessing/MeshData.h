#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

#include "Vertex.h"

namespace ssw
{
	struct MeshData
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}