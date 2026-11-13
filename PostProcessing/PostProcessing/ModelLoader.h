#pragma once

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <iostream>
#include <string>
#include <vector>

#include "MeshData.h"
#include "Vertex.h"

namespace ssw
{
	class ModelLoader
	{
	public:
		void Load(std::string basePath, std::string filename);

		void ProcessNode(aiNode* node,
			const aiScene* scene,
			DirectX::SimpleMath::Matrix parentTransform);

		MeshData ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:
		std::string _basePath;
		std::vector<MeshData> _meshes;
	};
}