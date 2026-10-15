#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace ssw
{
	using Microsoft::WRL::ComPtr;

	struct Mesh
	{
		ComPtr<ID3D11Buffer> vertexBuffer;
		ComPtr<ID3D11Buffer> indexBuffer;
		UINT _indexCount = 0;
	};
}