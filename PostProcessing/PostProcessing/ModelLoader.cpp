#include "ModelLoader.h"

#include <filesystem>

namespace ssw
{
	using namespace DirectX::SimpleMath;


	void ModelLoader::Load(std::string basePath, std::string filename)
	{
		_basePath = basePath;

		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(
			_basePath + filename,
			aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

		if (!pScene)
		{
			std::cout << "read file FAILED: " <<
				_basePath + filename << std::endl;
		}
		else
		{
			Matrix parentTransform;
			ProcessNode(pScene->mRootNode, pScene, parentTransform);
		}
	}

	void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, DirectX::SimpleMath::Matrix parentTransform)
	{
		Matrix localTransform;
		ai_real* src = &node->mTransformation.a1;
		float* dst = &localTransform._11;
		for (int i = 0; i < 16; ++i)
		{
			dst[i] = float(src[i]);
		}

		Matrix globalTransform = localTransform.Transpose() * parentTransform;

		for (UINT i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			auto newMesh = ProcessMesh(mesh, scene);

			for (auto& v : newMesh.vertices)
			{
				v.position = DirectX::SimpleMath::Vector3::Transform(v.position, globalTransform);
			}

			_meshes.push_back(newMesh);
		}

		for (UINT i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene, globalTransform);
		}
	}

	MeshData ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for (UINT i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex = {};

			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;

			if (mesh->mNormals)
			{
				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;
				vertex.normal.Normalize();
			}

			if (mesh->mTextureCoords[0])
			{
				vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
				vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
			}

			vertices.push_back(vertex);
		}

		for (UINT i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			
			for (UINT j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		MeshData meshData;
		meshData.vertices = vertices;
		meshData.indices = indices;

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString texturePath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

				std::string fullPath = _basePath +
					std::string(std::filesystem::path(texturePath.C_Str()).filename().string());
				
				meshData.textureFileName = fullPath;
			}
		}

		return meshData;
	}
	

}