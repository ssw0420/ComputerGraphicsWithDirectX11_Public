#include "DemoApp.h"

#include "GeometryGenerator.h"

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

namespace ssw
{
	DemoApp::DemoApp() : Application() {}

	bool DemoApp::Initialize()
	{
		if (!Application::Initialize()) return false;

		MeshData box = GeometryGenerator::MakeBox(0.3f);

		// CreateConstantBuffer
		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = sizeof(_basicVertexConstantData);
		cbDesc.Usage = D3D11_USAGE_DYNAMIC;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &_basicVertexConstantData;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		HRESULT hr = _device->CreateBuffer(&cbDesc, &initData, _vertexConstantBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::cout << "CreateConstantBuffer() FAILED" << std::hex << hr << std::dec << std::endl;
			return false;
		}

		// 메시 그룹 -> Buffer 생성

		// CreateVertexBuffer
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vbDesc.ByteWidth = UINT(sizeof(Vertex) * box.vertices.size());
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vbData = {};
		vbData.pSysMem = box.vertices.data();

		hr = _device->CreateBuffer(&vbDesc, &vbData, _box.vertexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::cout << "CreateVertexBuffer() FAILED " << std::hex << hr << std::dec << std::endl;
			return false;
		};

		// CreateIndexBuffer
		D3D11_BUFFER_DESC ibDesc = {};
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
		ibDesc.ByteWidth = UINT(sizeof(box.indices[0]) * box.indices.size());
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA ibData = {};
		ibData.pSysMem = box.indices.data();

		hr = _device->CreateBuffer(&ibDesc, &ibData, _box.indexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::cout << "CreateIndexBuffer() FAILED " << std::hex << hr << std::dec << std::endl;
			return false;
		}

		_box._indexCount = UINT(box.indices.size());
		
		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		// CreateVertexShaderAndInputLayout
		{
			ComPtr<ID3DBlob> vsBlob;
			ComPtr<ID3DBlob> errorBlob;

			hr = D3DCompileFromFile(L"BasicVS.hlsl",
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				"main",
				"vs_5_0",
				compileFlags,
				0,
				&vsBlob,
				&errorBlob);

			if (FAILED(hr))
			{
				if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
				{
					std::cout << "File not found: BasicVS.hlsl" << std::endl;
				}
				

				if (errorBlob)
				{
					std::cout << "Shader compile error\n" << (char*)errorBlob->GetBufferPointer() << std::endl;
				}

				std::cout << "HRESULT: " << std::hex << hr << std::dec << std::endl;
				return false;
			}

			_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

			vector<D3D11_INPUT_ELEMENT_DESC> inputElements =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			_device->CreateInputLayout(inputElements.data(),
				UINT(inputElements.size()),
				vsBlob->GetBufferPointer(),
				vsBlob->GetBufferSize(),
				_inputLayout.GetAddressOf()
			);
		}
		
		// CreatePixelShader
		{
			ComPtr<ID3DBlob> psBlob;
			ComPtr<ID3DBlob> errorBlob;

			hr = D3DCompileFromFile(L"BasicPS.hlsl",
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				"main",
				"ps_5_0",
				compileFlags,
				0,
				&psBlob,
				&errorBlob);

			if (FAILED(hr))
			{
				if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
					std::cout << "File not found: BasicPS.hlsl" << std::endl;

				if (errorBlob)
					std::cout << "Shader compile error\n" << (char*)errorBlob->GetBufferPointer() << std::endl;

				std::cout << "HRESULT: " << std::hex << hr << std::dec << std::endl;
				return false;
			}

			_device->CreatePixelShader(psBlob->GetBufferPointer(),
				psBlob->GetBufferSize(),
				nullptr,
				_pixelShader.GetAddressOf());
		}

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

		_context->RSSetState(_solidRasterizerState.Get());

		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		_context->IASetInputLayout(_inputLayout.Get());
		_context->IASetVertexBuffers(0, 1, _box.vertexBuffer.GetAddressOf(), &stride, &offset);
		_context->IASetIndexBuffer(_box.indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_context->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_context->PSSetShader(_pixelShader.Get(), nullptr, 0);

		_context->VSSetConstantBuffers(0, 1, _vertexConstantBuffer.GetAddressOf());

		_context->DrawIndexed(_box._indexCount, 0, 0);
	}

	void DemoApp::Update(float dt)
	{
		using namespace DirectX;

		auto modelRow = Matrix::CreateScale(_modelScaling);

		auto viewRow = Matrix::CreateTranslation(0.0f, 0.0f, 2.0f);

		const float aspect = Application::GetAspectRatio();
		auto projRow = static_cast<Matrix>(XMMatrixPerspectiveFovLH(XMConvertToRadians(_projFovAngleY), aspect, _nearZ, _farZ));
	
		_basicVertexConstantData.model = modelRow.Transpose();
		_basicVertexConstantData.view = viewRow.Transpose();
		_basicVertexConstantData.projection = projRow.Transpose();

		D3D11_MAPPED_SUBRESOURCE ms;
		_context->Map(_vertexConstantBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, &_basicVertexConstantData, sizeof(_basicVertexConstantData));
		
		_context->Unmap(_vertexConstantBuffer.Get(), NULL);
	}
}