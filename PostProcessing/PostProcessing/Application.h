#pragma once

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <iostream>
#include <vector>

#include "D3D11Utils.h"

namespace ssw
{
	using Microsoft::WRL::ComPtr;
	using std::shared_ptr;
	using std::vector;
	using std::wstring;

	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		virtual bool Initialize();
		virtual void Render() = 0;

		int Run();

		virtual void Update(float dt) = 0;
		float GetAspectRatio() const;

		virtual void UpdateGUI() = 0;

	protected:
		void SetViewport();

	private:
		bool InitMainWindow();
		bool InitDirect3D();
		bool InitGUI();

		void CreateDepthBuffer();
		void CreateRasterizerStates();

	public:
		int _screenWidth = 0;
		int _screenHeight = 0;
		HWND _mainWindow;
		D3D11_VIEWPORT _screenViewport;

		int _guiWidth = 0;

		UINT numQualityLevels = 0;

		ComPtr<ID3D11Device> _device;
		ComPtr<ID3D11DeviceContext> _context;
		ComPtr<IDXGISwapChain> _swapChain;
		ComPtr<ID3D11RenderTargetView>_renderTargetView;
		ComPtr<ID3D11ShaderResourceView>_shaderResourceView;

		// Depth buffer
		ComPtr<ID3D11DepthStencilView> _depthStencilView;
		ComPtr<ID3D11DepthStencilState> _depthStencilState;

		// Rasterizer
		ComPtr<ID3D11RasterizerState> _solidRasterizerState;
		ComPtr<ID3D11RasterizerState> _wireRasterizerState;
	};
}