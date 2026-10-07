#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <wrl.h> // ComPtr

namespace ssw
{
	using Microsoft::WRL::ComPtr;
	using std::shared_ptr;
	using std::vector;
	using std::wstring;

}