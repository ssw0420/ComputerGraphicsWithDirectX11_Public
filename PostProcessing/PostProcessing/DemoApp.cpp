#include "DemoApp.h"

#include "GeometryGenerator.h"

namespace ssw
{
	DemoApp::DemoApp() : Application() {}

	bool DemoApp::Initialize()
	{
		if (!Application::Initialize()) return false;
		MeshData sphere = GeometryGenerator::MakeSphere(0.3f, 100, 100);
		sphere.textureFileName = "earth.jpg";
		_meshGroupSphere.Initialize(_device, { sphere });

		MeshData box = GeometryGenerator::MakeBox(0.3f);
		box.textureFileName = "wall.jpg";
		_meshGroupBox.Initialize(_device, { box });

		_meshGroupCharacter.Initialize(_device, "C:/Portfolio/models/", "character.fbx");

		Material material;
		material.diffuse = Vector3(1.0f);
		material.ambient = Vector3(0.1f);
		material.shininess = 10.0f;
		_meshGroupSphere._basicPixelConstantData.material = material;
		_meshGroupBox._basicPixelConstantData.material = material;
		_meshGroupCharacter._basicPixelConstantData.material = material;

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
		if (_bCharacterVisible) _meshGroupCharacter.Render(_context);

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
	
		auto eyeWorld = Vector3::Transform(Vector3(0.0f), viewRow.Invert());
		_meshGroupSphere._basicPixelConstantData.eyeWorld = eyeWorld;
		_meshGroupBox._basicPixelConstantData.eyeWorld = eyeWorld;
		_meshGroupCharacter._basicPixelConstantData.eyeWorld = eyeWorld;

		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			Light light = _guiLight;
			light.direction.Normalize();

			if (i != _lightType)
			{
				light.strength *= 0.0f;
			}

			_meshGroupSphere._basicPixelConstantData.lights[i] = light;
			_meshGroupBox._basicPixelConstantData.lights[i] = light;
			_meshGroupCharacter._basicPixelConstantData.lights[i] = light;
		}

		// 두 물체를 동시에 표현하기 위해 위치도 조정함
		// 왼쪽 -> 오른쪽 순서
		auto sphereModelRow = Matrix::CreateScale(_sphereTransform.scaling) *
			Matrix::CreateRotationY(_sphereTransform.rotation.y) *
			Matrix::CreateRotationX(_sphereTransform.rotation.x) *
			Matrix::CreateRotationZ(_sphereTransform.rotation.z) *
			Matrix::CreateTranslation(_sphereTransform.translation);
		auto sphereInvTransposeRow = sphereModelRow.Invert().Transpose();
		_meshGroupSphere._basicVertexConstantData.model = sphereModelRow.Transpose();
		_meshGroupSphere._basicVertexConstantData.view = viewRow.Transpose();
		_meshGroupSphere._basicVertexConstantData.projection = projRow.Transpose();
		_meshGroupSphere._basicVertexConstantData.invTranspose = sphereInvTransposeRow.Transpose();
		_meshGroupSphere.UpdateConstantBuffers(_device, _context);

		auto boxModelRow = Matrix::CreateScale(_boxTransform.scaling) *
			Matrix::CreateRotationY(_boxTransform.rotation.y) *
			Matrix::CreateRotationX(_boxTransform.rotation.x) *
			Matrix::CreateRotationZ(_boxTransform.rotation.z) *
			Matrix::CreateTranslation(_boxTransform.translation);
		auto boxInvTransposeRow = boxModelRow.Invert().Transpose();
		_meshGroupBox._basicVertexConstantData.model = boxModelRow.Transpose();
		_meshGroupBox._basicVertexConstantData.view = viewRow.Transpose();
		_meshGroupBox._basicVertexConstantData.projection = projRow.Transpose();
		_meshGroupBox._basicVertexConstantData.invTranspose = boxInvTransposeRow.Transpose();
		_meshGroupBox.UpdateConstantBuffers(_device, _context);

		auto characterModelRow = Matrix::CreateScale(_characterTransform.scaling) *
			Matrix::CreateRotationY(_characterTransform.rotation.y) *
			Matrix::CreateRotationX(_characterTransform.rotation.x) *
			Matrix::CreateRotationZ(_characterTransform.rotation.z) *
			Matrix::CreateTranslation(_characterTransform.translation);
		auto characterInvTransposeRow = characterModelRow.Invert().Transpose();
		_meshGroupCharacter._basicVertexConstantData.model = characterModelRow.Transpose();
		_meshGroupCharacter._basicVertexConstantData.view = viewRow.Transpose();
		_meshGroupCharacter._basicVertexConstantData.projection = projRow.Transpose();
		_meshGroupCharacter._basicVertexConstantData.invTranspose = characterInvTransposeRow.Transpose();
		_meshGroupCharacter.UpdateConstantBuffers(_device, _context);
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
				_guiTransform = _sphereTransform;
				_bDrawNormals = _meshGroupSphere._bDrawNormals;
				_normalScale = _meshGroupSphere._normalVertexConstantData.scale;
				_bUseTexture = _meshGroupSphere._basicPixelConstantData.useTexture;
			}
			else if (_bBoxSelected)
			{
				_guiTransform = _boxTransform;
				_bDrawNormals = _meshGroupBox._bDrawNormals;
				_normalScale = _meshGroupBox._normalVertexConstantData.scale;
				_bUseTexture = _meshGroupBox._basicPixelConstantData.useTexture;
			}
			else if (_bCharacterSelected)
			{
				_guiTransform = _characterTransform;
				_bDrawNormals = _meshGroupCharacter._bDrawNormals;
				_bUseTexture = _meshGroupCharacter._basicPixelConstantData.useTexture;
				_normalScale = _meshGroupCharacter._normalVertexConstantData.scale;
			}
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Box", &_bBoxSelected))
		{
			if (_bSphereSelected)
			{
				_guiTransform = _sphereTransform;
				_bDrawNormals = _meshGroupSphere._bDrawNormals;
				_normalScale = _meshGroupSphere._normalVertexConstantData.scale;
				_bUseTexture = _meshGroupSphere._basicPixelConstantData.useTexture;
			}
			else if (_bBoxSelected)
			{
				_guiTransform = _boxTransform;
				_bDrawNormals = _meshGroupBox._bDrawNormals;
				_normalScale = _meshGroupBox._normalVertexConstantData.scale;
				_bUseTexture = _meshGroupBox._basicPixelConstantData.useTexture;
			}
			else if (_bCharacterSelected)
			{
				_guiTransform = _characterTransform;
				_bDrawNormals = _meshGroupCharacter._bDrawNormals;
				_bUseTexture = _meshGroupCharacter._basicPixelConstantData.useTexture;
				_normalScale = _meshGroupCharacter._normalVertexConstantData.scale;
			}
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Character", &_bCharacterSelected))
		{
			if (_bSphereSelected)
			{
				_guiTransform = _sphereTransform;
				_bDrawNormals = _meshGroupSphere._bDrawNormals;
				_normalScale = _meshGroupSphere._normalVertexConstantData.scale;
				_bUseTexture = _meshGroupSphere._basicPixelConstantData.useTexture;
			}
			else if (_bBoxSelected)
			{
				_guiTransform = _boxTransform;
				_bDrawNormals = _meshGroupBox._bDrawNormals;
				_normalScale = _meshGroupBox._normalVertexConstantData.scale;
				_bUseTexture = _meshGroupBox._basicPixelConstantData.useTexture;
			}
			else if (_bCharacterSelected)
			{
				_guiTransform = _characterTransform;
				_bDrawNormals = _meshGroupCharacter._bDrawNormals;
				_bUseTexture = _meshGroupCharacter._basicPixelConstantData.useTexture;
				_normalScale = _meshGroupCharacter._normalVertexConstantData.scale;
			}
		}

		ImGui::Checkbox("Show Sphere", &_bSphereVisible);
		ImGui::SameLine();
		ImGui::Checkbox("Show Box", &_bBoxVisible);
		ImGui::SameLine();
		ImGui::Checkbox("Show Character", &_bCharacterVisible);

		if (ImGui::SliderFloat3("Model Translation", &_guiTransform.translation.x, -1.0f, 1.0f))
		{
			if (_bSphereSelected) _sphereTransform.translation = _guiTransform.translation;
			if (_bBoxSelected) _boxTransform.translation = _guiTransform.translation;
			if (_bCharacterSelected) _characterTransform.translation = _guiTransform.translation;
		}

		if (ImGui::SliderFloat3("Model Rotation", &_guiTransform.rotation.x, -3.14f, 3.14f))
		{
			if (_bSphereSelected) _sphereTransform.rotation = _guiTransform.rotation;
			if (_bBoxSelected) _boxTransform.rotation = _guiTransform.rotation;
			if (_bCharacterSelected) _characterTransform.rotation = _guiTransform.rotation;
		}

		bool bScaleChanged = false;
		ImGui::Checkbox("##UniformScale", &_bUniformScale);
		ImGui::SameLine();
		if (_bUniformScale)
		{
			float uniformScale = _guiTransform.scaling.x;
			if (ImGui::SliderFloat("Model Scaling", &uniformScale, 0.1f, 3.0f))
			{
				_guiTransform.scaling = Vector3(uniformScale);
				bScaleChanged = true;
			}
		}
		else
		{
			bScaleChanged = ImGui::SliderFloat3("Model Scaling", &_guiTransform.scaling.x, 0.1f, 3.0f);
		}

		if (bScaleChanged)
		{
			if (_bSphereSelected) _sphereTransform.scaling = _guiTransform.scaling;
			if (_bBoxSelected) _boxTransform.scaling = _guiTransform.scaling;
			if (_bCharacterSelected) _characterTransform.scaling = _guiTransform.scaling;
		}

		ImGui::SliderFloat2("_viewRot", &_viewRot.x, -3.14f, 3.14f);

		ImGui::Checkbox("Wireframe", &_bDrawAsWire);

		if (ImGui::Checkbox("Use Texture", &_bUseTexture))
		{
			if (_bSphereSelected) _meshGroupSphere._basicPixelConstantData.useTexture = _bUseTexture;
			if (_bBoxSelected) _meshGroupBox._basicPixelConstantData.useTexture = _bUseTexture;
			if (_bCharacterSelected) _meshGroupCharacter._basicPixelConstantData.useTexture = _bUseTexture;
		}

		if (ImGui::Checkbox("Draw Normals", &_bDrawNormals))
		{
			_meshGroupSphere._bDrawNormals = _bDrawNormals;
			_meshGroupBox._bDrawNormals = _bDrawNormals;
			_meshGroupCharacter._bDrawNormals = _bDrawNormals;
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

			if (_bCharacterSelected)
			{
				_meshGroupCharacter._normalVertexConstantData.scale = _normalScale;
				_meshGroupCharacter._bDrawNormalsDirtyFlag = true;
			}
		}

		if (ImGui::RadioButton("Directional", _lightType == 0))
		{
			_lightType = 0;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Point", _lightType == 1))
		{
			_lightType = 1;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Spot", _lightType == 2))
		{
			_lightType = 2;
		}

		ImGui::SliderFloat3("Light Position", &_guiLight.position.x, -3.0f, 3.0f);
		ImGui::SliderFloat3("Light Direction", &_guiLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot Power", &_guiLight.spotPower, 1.0f, 200.0f);

		if (ImGui::SliderFloat("Material Diffuse", &_guiMaterialDiffuse, 0.0f, 3.0f))
		{
			if (_bSphereSelected) _meshGroupSphere._basicPixelConstantData.material.diffuse = Vector3(_guiMaterialDiffuse);
			if (_bBoxSelected) _meshGroupBox._basicPixelConstantData.material.diffuse = Vector3(_guiMaterialDiffuse);
			if (_bCharacterSelected) _meshGroupCharacter._basicPixelConstantData.material.diffuse = Vector3(_guiMaterialDiffuse);
		}

		if (ImGui::SliderFloat("Material Specular", &_guiMaterialSpecular, 0.0f, 3.0f))
		{
			if (_bSphereSelected) _meshGroupSphere._basicPixelConstantData.material.specular = Vector3(_guiMaterialSpecular);
			if (_bBoxSelected) _meshGroupBox._basicPixelConstantData.material.specular = Vector3(_guiMaterialSpecular);
			if (_bCharacterSelected) _meshGroupCharacter._basicPixelConstantData.material.specular = Vector3(_guiMaterialSpecular);
		}

		if (ImGui::SliderFloat("Material Shininess", &_guiMaterialShininess, 0.01f, 20.0f))
		{
			if (_bSphereSelected) _meshGroupSphere._basicPixelConstantData.material.shininess = _guiMaterialShininess;
			if (_bBoxSelected) _meshGroupBox._basicPixelConstantData.material.shininess = _guiMaterialShininess;
			if (_bCharacterSelected) _meshGroupCharacter._basicPixelConstantData.material.shininess = _guiMaterialShininess;
		}

	}
}