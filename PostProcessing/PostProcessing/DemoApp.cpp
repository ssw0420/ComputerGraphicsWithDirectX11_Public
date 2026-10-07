#include "DemoApp.h"

namespace ssw
{
	DemoApp::DemoApp() : Application() {}

	bool DemoApp::Initialize()
	{
		if (!Application::Initialize()) return false;

		return true;
	}

	void DemoApp::Render()
	{
		SetViewport();

		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		_context->ClearRenderTargetView(_renderTargetView.Get(), clearColor);
		_context->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
		_context->OMSetDepthStencilState(_depthStencilState.Get(), 0);

		_context->RSSetState(_solidRasterizerSate.Get());
	}
}