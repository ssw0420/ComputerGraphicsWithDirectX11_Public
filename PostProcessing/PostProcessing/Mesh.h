#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace ssw
{
	using Microsoft::WRL::ComPtr;

	struct Mesh
	{
		ComPtr<ID3D11Buffer> _vertexBuffer;
		ComPtr<ID3D11Buffer> _indexBuffer;
		UINT _indexCount = 0;
	};
}