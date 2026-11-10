#include "DemoApp.h"

#include "GeometryGenerator.h"

namespace ssw
{
	DemoApp::DemoApp() : Application() {}

	bool DemoApp::Initialize()
	{
		if (!Application::Initialize()) return false;
		MeshData sphere = GeometryGenerator::MakeSphere(0.3f, 100, 100);
		_meshGroupSphere.Initialize(_device, { sphere });

		MeshData box = GeometryGenerator::MakeBox(0.3f);
		_meshGroupBox.Initialize(_device, { box });

		return true;

		//MeshData box = GeometryGenerator::MakeBox(0.3f);
		//MeshData mesh = GeometryGenerator::MakeCylinder(0.3f, 0.3f, 0.6f, 20);
		

		// CreateConstantBuffer
		//D3D11_BUFFER_DESC cbDesc;
		//cbDesc.ByteWidth = sizeof(_basicVertexConstantData);
		//cbDesc.Usage = D3D11_USAGE_DYNAMIC;
		//cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//cbDesc.MiscFlags = 0;
		//cbDesc.StructureByteStride = 0;

		//D3D11_SUBRESOURCE_DATA initData;
		//initData.pSysMem = &_basicVertexConstantData;
		//initData.SysMemPitch = 0;
		//initData.SysMemSlicePitch = 0;

		//HRESULT hr = _device->CreateBuffer(&cbDesc, &initData, _vertexConstantBuffer.GetAddressOf());
		//if (FAILED(hr))
		//{
		//	std::cout << "CreateConstantBuffer() FAILED" << std::hex << hr << std::dec << std::endl;
		//	return false;
		//}

		// 메시 그룹 -> Buffer 생성

		// CreateVertexBuffer
		//D3D11_BUFFER_DESC vbDesc = {};
		//vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
		//vbDesc.ByteWidth = UINT(sizeof(Vertex) * mesh.vertices.size());
		//vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//D3D11_SUBRESOURCE_DATA vbData = {};
		//vbData.pSysMem = mesh.vertices.data();

		//hr = _device->CreateBuffer(&vbDesc, &vbData, _mesh.vertexBuffer.GetAddressOf());
		//if (FAILED(hr))
		//{
		//	std::cout << "CreateVertexBuffer() FAILED " << std::hex << hr << std::dec << std::endl;
		//	return false;
		//};

		// CreateIndexBuffer
		//D3D11_BUFFER_DESC ibDesc = {};
		//ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
		//ibDesc.ByteWidth = UINT(sizeof(mesh.indices[0]) * mesh.indices.size());
		//ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		//D3D11_SUBRESOURCE_DATA ibData = {};
		//ibData.pSysMem = mesh.indices.data();

		//hr = _device->CreateBuffer(&ibDesc, &ibData, _mesh.indexBuffer.GetAddressOf());
		//if (FAILED(hr))
		//{
		//	std::cout << "CreateIndexBuffer() FAILED " << std::hex << hr << std::dec << std::endl;
		//	return false;
		//}

		//_mesh._indexCount = UINT(mesh.indices.size());
		
//		UINT compileFlags = 0;
//#if defined(DEBUG) || defined(_DEBUG)
//		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif

		// CreateVertexShaderAndInputLayout
		{
			//ComPtr<ID3DBlob> vsBlob;
			//ComPtr<ID3DBlob> errorBlob;

			//hr = D3DCompileFromFile(L"BasicVS.hlsl",
			//	nullptr,
			//	D3D_COMPILE_STANDARD_FILE_INCLUDE,
			//	"main",
			//	"vs_5_0",
			//	compileFlags,
			//	0,
			//	&vsBlob,
			//	&errorBlob);

			//if (FAILED(hr))
			//{
			//	if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			//	{
			//		std::cout << "File not found: BasicVS.hlsl" << std::endl;
			//	}
			//	

			//	if (errorBlob)
			//	{
			//		std::cout << "Shader compile error\n" << (char*)errorBlob->GetBufferPointer() << std::endl;
			//	}

			//	std::cout << "HRESULT: " << std::hex << hr << std::dec << std::endl;
			//	return false;
			//}

			//_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

			//vector<D3D11_INPUT_ELEMENT_DESC> inputElements =
			//{
			//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			//	{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
			//};

			//_device->CreateInputLayout(inputElements.data(),
			//	UINT(inputElements.size()),
			//	vsBlob->GetBufferPointer(),
			//	vsBlob->GetBufferSize(),
			//	_inputLayout.GetAddressOf()
			//);
		}
		
		// CreatePixelShader
		{
			//ComPtr<ID3DBlob> psBlob;
			//ComPtr<ID3DBlob> errorBlob;

			//hr = D3DCompileFromFile(L"BasicPS.hlsl",
			//	nullptr,
			//	D3D_COMPILE_STANDARD_FILE_INCLUDE,
			//	"main",
			//	"ps_5_0",
			//	compileFlags,
			//	0,
			//	&psBlob,
			//	&errorBlob);

			//if (FAILED(hr))
			//{
			//	if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			//		std::cout << "File not found: BasicPS.hlsl" << std::endl;

			//	if (errorBlob)
			//		std::cout << "Shader compile error\n" << (char*)errorBlob->GetBufferPointer() << std::endl;

			//	std::cout << "HRESULT: " << std::hex << hr << std::dec << std::endl;
			//	return false;
			//}

			//_device->CreatePixelShader(psBlob->GetBufferPointer(),
			//	psBlob->GetBufferSize(),
			//	nullptr,
			//	_pixelShader.GetAddressOf());
		}
	}

	void DemoApp::Render()
	{
		SetViewport();

		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		_context->ClearRenderTargetView(_renderTargetView.Get(), clearColor);
		_context->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
		_context->OMSetDepthStencilState(_depthStencilState.Get(), 0);

		if (_bDrawAsWire)
		{
			_context->RSSetState(_wireRasterizerState.Get());
		}
		else
		{
			_context->RSSetState(_solidRasterizerState.Get());
		}

		if (_bSphereVisible) _meshGroupSphere.Render(_context);
		if (_bBoxVisible) _meshGroupBox.Render(_context);

		//UINT stride = sizeof(Vertex);
		//UINT offset = 0;

		//_context->IASetInputLayout(_inputLayout.Get());
		//_context->IASetVertexBuffers(0, 1, _mesh.vertexBuffer.GetAddressOf(), &stride, &offset);
		//_context->IASetIndexBuffer(_mesh.indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		//_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//_context->VSSetShader(_vertexShader.Get(), nullptr, 0);
		//_context->PSSetShader(_pixelShader.Get(), nullptr, 0);

		//_context->VSSetConstantBuffers(0, 1, _vertexConstantBuffer.GetAddressOf());

		//_context->DrawIndexed(_mesh._indexCount, 0, 0);
	}

	void DemoApp::Update(float dt)
	{
		using namespace DirectX;

		//auto modelRow = Matrix::CreateScale(_modelScaling);

		auto viewRow = Matrix::CreateRotationY(_viewRot.y) *
			Matrix::CreateRotationX(_viewRot.x) *
			Matrix::CreateTranslation(0.0f, 0.0f, 2.0f);

		const float aspect = Application::GetAspectRatio();
		auto projRow = static_cast<Matrix>(XMMatrixPerspectiveFovLH(XMConvertToRadians(_projFovAngleY), aspect, _nearZ, _farZ));
	
		// 두 물체를 동시에 표현하기 위해 위치도 조정함
		// 행 벡터이므로 왼쪽 -> 오른쪽 순서
		auto sphereModelRow = Matrix::CreateScale(_sphereScaling) *
			Matrix::CreateRotationY(_sphereRotation.y) *
			Matrix::CreateRotationX(_sphereRotation.x) *
			Matrix::CreateRotationZ(_sphereRotation.z) *
			Matrix::CreateTranslation(_sphereTranslation);
		auto sphereInvTransposeRow = sphereModelRow.Invert().Transpose();
		_meshGroupSphere._basicVertexConstantData.model = sphereModelRow.Transpose();
		_meshGroupSphere._basicVertexConstantData.view = viewRow.Transpose();
		_meshGroupSphere._basicVertexConstantData.projection = projRow.Transpose();
		_meshGroupSphere._basicVertexConstantData.invTranspose = sphereInvTransposeRow.Transpose();
		_meshGroupSphere.UpdateConstantBuffers(_device, _context);

		auto boxModelRow = Matrix::CreateScale(_boxScaling) *
			Matrix::CreateRotationY(_boxRotation.y) *
			Matrix::CreateRotationX(_boxRotation.x) *
			Matrix::CreateRotationZ(_boxRotation.z) *
			Matrix::CreateTranslation(_boxTranslation);
		auto boxInvTransposeRow = boxModelRow.Invert().Transpose();
		_meshGroupBox._basicVertexConstantData.model = boxModelRow.Transpose();
		_meshGroupBox._basicVertexConstantData.view = viewRow.Transpose();
		_meshGroupBox._basicVertexConstantData.projection = projRow.Transpose();
		_meshGroupBox._basicVertexConstantData.invTranspose = boxInvTransposeRow.Transpose();
		_meshGroupBox.UpdateConstantBuffers(_device, _context);

		//D3D11_MAPPED_SUBRESOURCE ms;
		//_context->Map(_vertexConstantBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		//memcpy(ms.pData, &_basicVertexConstantData, sizeof(_basicVertexConstantData));
		//
		//_context->Unmap(_vertexConstantBuffer.Get(), NULL);
	}

	void DemoApp::UpdateGUI()
	{
		if (ImGui::Checkbox("Sphere", &_bSphereSelected))
		{
			if (_bSphereSelected)
			{
				_modelRotation = _sphereRotation;
				_modelTranslation = _sphereTranslation;
				_modelScaling = _sphereScaling;
				_bDrawNormals = _meshGroupSphere._bDrawNormals;
				_normalScale = _meshGroupSphere._normalVertexConstantData.scale;
			}
			else if (_bBoxSelected)
			{
				_modelRotation = _boxRotation;
				_modelTranslation = _boxTranslation;
				_modelScaling = _boxScaling;
				_bDrawNormals = _meshGroupBox._bDrawNormals;
				_normalScale = _meshGroupBox._normalVertexConstantData.scale;
			}
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Box", &_bBoxSelected))
		{
			if (_bSphereSelected)
			{
				_modelRotation = _sphereRotation;
				_modelTranslation = _sphereTranslation;
				_modelScaling = _sphereScaling;
				_bDrawNormals = _meshGroupSphere._bDrawNormals;
				_normalScale = _meshGroupSphere._normalVertexConstantData.scale;
			}
			else if (_bBoxSelected)
			{
				_modelRotation = _boxRotation;
				_modelTranslation = _boxTranslation;
				_modelScaling = _boxScaling;
				_bDrawNormals = _meshGroupBox._bDrawNormals;
				_normalScale = _meshGroupBox._normalVertexConstantData.scale;
			}
		}

		ImGui::Checkbox("Show Sphere", &_bSphereVisible);
		ImGui::SameLine();
		ImGui::Checkbox("Show Box", &_bBoxVisible);

		if (ImGui::SliderFloat3("Model Translation", &_modelTranslation.x, -1.0f, 1.0f))
		{
			if (_bSphereSelected) _sphereTranslation = _modelTranslation;
			if (_bBoxSelected) _boxTranslation = _modelTranslation;
		}

		if (ImGui::SliderFloat3("Model Rotation", &_modelRotation.x, -3.14f, 3.14f))
		{
			if (_bSphereSelected) _sphereRotation = _modelRotation;
			if (_bBoxSelected) _boxRotation = _modelRotation;
		}

		if (ImGui::SliderFloat3("Model Scaling", &_modelScaling.x, 0.1f, 3.0f))
		{
			if (_bSphereSelected) _sphereScaling = _modelScaling;
			if (_bBoxSelected) _boxScaling = _modelScaling;
		}

		ImGui::SliderFloat2("_viewRot", &_viewRot.x, -3.14f, 3.14f);

		ImGui::Checkbox("Wireframe", &_bDrawAsWire);

		if (ImGui::Checkbox("Draw Normals", &_bDrawNormals))
		{
			if (_bSphereSelected) _meshGroupSphere._bDrawNormals = _bDrawNormals;
			if (_bBoxSelected) _meshGroupBox._bDrawNormals = _bDrawNormals;
		}

		if (ImGui::SliderFloat("Normal Scale", &_normalScale, 0.0f, 0.1f))
		{
			if (_bSphereSelected)
			{
				_meshGroupSphere._normalVertexConstantData.scale = _normalScale;
				_meshGroupSphere._bDrawNormalsDirtyFlag = true;
			}
			
			if (_bBoxSelected)
			{
				_meshGroupBox._normalVertexConstantData.scale = _normalScale;
				_meshGroupBox._bDrawNormalsDirtyFlag = true;
			}
		}

	}
}