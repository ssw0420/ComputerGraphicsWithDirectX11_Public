#include "Application.h"
#include "D3D11Utils.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ssw
{
	using namespace std;

	Application* g_application = nullptr;

	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam)
	{
		return g_application->MsgProc(hWnd, msg, wParam, lparam);
	}

	Application::Application()
		: _screenWidth(1920), _screenHeight(1080), _mainWindow(0), _screenViewport(D3D11_VIEWPORT())
	{
		g_application = this;
	}

	Application::~Application()
	{
		g_application = nullptr;

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		DestroyWindow(_mainWindow);
	}



	bool Application::Initialize()
	{
		if (!InitMainWindow()) return false;

		if (!InitDirect3D()) return false;

		if (!InitGUI()) return false;

		return true;
	}

	LRESULT Application::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;

		switch (msg)
		{
		case WM_SIZE:
			if (_swapChain)
			{
				_screenWidth = int(LOWORD(lParam));
				_screenHeight = int(HIWORD(lParam));
				_guiWidth = 0;

				_renderTargetView.Reset();
				_shaderResourceView.Reset();
				_swapChain->ResizeBuffers
				(
					0,
					(UINT)LOWORD(lParam),
					(UINT)HIWORD(lParam),
					DXGI_FORMAT_UNKNOWN,
					0
				);
				
				// CreateRenderTargetView
				ComPtr<ID3D11Texture2D> backBuffer;
				_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));

				if (backBuffer)
				{
					_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
					_device->CreateShaderResourceView(backBuffer.Get(), nullptr, _shaderResourceView.GetAddressOf());
				}
				else
				{
					std::cout << "CreateRenderTargetView() FAILED" << std::endl;
				}

				// CreateDepthBuffer
				CreateDepthBuffer();

				// SetViewport
				SetViewport();
			}

			break;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) return 0;

			break;
		case WM_MOUSEMOVE:
			// cout << "Mouse " << LOWORD(lParam) << " " << HIWORD(lParam) << endl;
			break;
		case WM_LBUTTONUP:
			// cout << "WM_LBUTTONUP Left mouse button" << endl;
			break;
		case WM_RBUTTONUP:
			// cout << "WM_RBUTTONUP Right mouse button" << endl;
			break;
		case WM_KEYDOWN:
			// cout << "WM_KEYDOWN " << (int)wParam << endl;
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
		}

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	int Application::Run()
	{
		MSG msg = { 0 };

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();

				ImGui::NewFrame();
				ImGui::Begin("Scene Control");

				ImGui::Text("Average %.3f ms/frame (%.1f FPS)",
					1000.0f / ImGui::GetIO().Framerate,
					ImGui::GetIO().Framerate);

				_guiWidth = 0;

				ImGui::End();
				ImGui::Render();

				Render();

				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

				_swapChain->Present(1, 0);
				
			}
		}

		return 0;
	}

	bool Application::InitMainWindow()
	{
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WndProc,
			0L,
			0L,
			GetModuleHandle(NULL),
			NULL,
			NULL,
			NULL,
			NULL,
			L"ComputerGraphicsDEMO",
			NULL
		};

		if (!RegisterClassEx(&wc))
		{
			cout << "RegisterClassEx() FAILED" << endl;
			return false;
		}

		RECT wr = { 0, 0, _screenWidth, _screenHeight };

		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);
		_mainWindow = CreateWindow(wc.lpszClassName,
			L"Graphics DEMO",
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			wr.right - wr.left,
			wr.bottom - wr.top,
			NULL,
			NULL,
			wc.hInstance,
			NULL);

		if (!_mainWindow)
		{
			cout << "CreateWindow() FAILED" << endl;
			return false;
		}

		ShowWindow(_mainWindow, SW_SHOWDEFAULT);
		UpdateWindow(_mainWindow);

		return true;
	}

	bool Application::InitDirect3D()
	{
		const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		const D3D_FEATURE_LEVEL featureLevels[2] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_9_3
		};
		D3D_FEATURE_LEVEL featureLevel;

		if (FAILED(D3D11CreateDevice(
			nullptr,    // Specify nullptr to use the default adapter.
			driverType, // Create a device using the hardware graphics driver.
			0, // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			createDeviceFlags, // Set debug and Direct2D compatibility flags.
			featureLevels,     // List of feature levels this app can support.
			ARRAYSIZE(featureLevels), // Size of the list above.
			D3D11_SDK_VERSION,     // Always set this to D3D11_SDK_VERSION for
			// Microsoft Store apps.
			device.GetAddressOf(), // Returns the Direct3D device created.
			&featureLevel,         // Returns feature level of device created.
			context.GetAddressOf() // Returns the device immediate context.
		)))
		{
			cout << "D3D11CreateDevice() FAILED" << endl;
			return false;
		}

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			cout << "D3D Feature Level 11 unsupported." << endl;
			return false;
		}

		device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &numQualityLevels);

		if (numQualityLevels <= 0)
		{
			cout << "MSAA not supported." << endl;
		}

		if (FAILED(device.As(&_device)))
		{
			cout << "device.AS() failed." << endl;
			return false;
		}

		if (FAILED(context.As(&_context)))
		{
			cout << "context.As() failed." << endl;
			return false;
		}

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = _screenWidth;   // set the back buffer width
		sd.BufferDesc.Height = _screenHeight; // set the back buffer height
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color
		sd.BufferCount = 2;                                // Double-buffering
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;

		sd.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = _mainWindow; // the window to be used
		sd.Windowed = TRUE;             // windowed/full-screen mode
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		if (numQualityLevels > 0)
		{
			sd.SampleDesc.Count = 4; // how many multisamples
			sd.SampleDesc.Quality = numQualityLevels - 1;
		}
		else // 지원 안하는 경우
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}

		if (FAILED(D3D11CreateDeviceAndSwapChain(
			0, // Default adapter
			driverType,
			0, // No software device
			createDeviceFlags, featureLevels, 1, D3D11_SDK_VERSION, &sd,
			_swapChain.GetAddressOf(), _device.GetAddressOf(), &featureLevel,
			_context.GetAddressOf())))
		{
			cout << "D3D11CreateDeviceAndSwapChain() failed." << endl;
			return false;
		}

		// CreateRenderTargetView
		ComPtr<ID3D11Texture2D> backBuffer;
		_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
		if (backBuffer)
		{
			_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
			_device->CreateShaderResourceView(backBuffer.Get(), nullptr, _shaderResourceView.GetAddressOf());
		}
		else
		{
			std::cout << "CreateRenderTargetView() failed." << std::endl;
			return false;
		}
		
		// SetViewport
		SetViewport();

		// Create RasterizerState
		CreateRasterizerStates();
		
		// CreateDepthBuffer
		CreateDepthBuffer();

		// CreateDepthStencilState
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		if (FAILED(_device->CreateDepthStencilState(&depthStencilDesc, _depthStencilState.GetAddressOf())))
		{
			cout << "CreateDepthStencilState() FAILED" << endl;
		}

		return true;
	}

	void Application::SetViewport()
	{
		ZeroMemory(&_screenViewport, sizeof(D3D11_VIEWPORT));
		_screenViewport.TopLeftX = float(_guiWidth);
		_screenViewport.TopLeftY = 0;
		_screenViewport.Width = float(_screenWidth - _guiWidth);
		_screenViewport.Height = float(_screenHeight);
		// m_screenViewport.Width = static_cast<float>(m_screenHeight);
		_screenViewport.MinDepth = 0.0f;
		_screenViewport.MaxDepth = 1.0f; // Note: important for depth buffering

		_context->RSSetViewports(1, &_screenViewport);
	}

	void Application::CreateRasterizerStates()
	{
		D3D11_RASTERIZER_DESC rastDesc;
		ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
		rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.DepthClipEnable = true;

		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		_device->CreateRasterizerState(&rastDesc, _solidRasterizerSate.GetAddressOf());
	
		rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		_device->CreateRasterizerState(&rastDesc, _wireRasterizerSate.GetAddressOf());
	}

	void Application::CreateDepthBuffer()
	{
		D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
		depthStencilBufferDesc.Width = _screenWidth;
		depthStencilBufferDesc.Height = _screenHeight;
		depthStencilBufferDesc.MipLevels = 1;
		depthStencilBufferDesc.ArraySize = 1;
		depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (numQualityLevels > 0)
		{
			depthStencilBufferDesc.SampleDesc.Count = 4; // how many multisamples
			depthStencilBufferDesc.SampleDesc.Quality = numQualityLevels - 1;
		}
		else
		{
			depthStencilBufferDesc.SampleDesc.Count = 1; // how many multisamples
			depthStencilBufferDesc.SampleDesc.Quality = 0;
		}
		depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilBufferDesc.CPUAccessFlags = 0;
		depthStencilBufferDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> depthStencilBuffer;

		if (FAILED(_device->CreateTexture2D(&depthStencilBufferDesc, 0,
			depthStencilBuffer.GetAddressOf())))
		{
			std::cout << "CreateTexture2D() failed." << std::endl;
		}

		if (FAILED(_device->CreateDepthStencilView(
			depthStencilBuffer.Get(), 0, _depthStencilView.GetAddressOf())))
		{
			std::cout << "CreateDepthStencilView() failed." << std::endl;
		}
	}

	bool Application::InitGUI()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		
		io.DisplaySize = ImVec2(float(_screenWidth), float(_screenHeight));
		ImGui::StyleColorsClassic();

		if (!ImGui_ImplDX11_Init(_device.Get(), _context.Get())) return false;
		if (!ImGui_ImplWin32_Init(_mainWindow)) return false;

		return true;
	}
}