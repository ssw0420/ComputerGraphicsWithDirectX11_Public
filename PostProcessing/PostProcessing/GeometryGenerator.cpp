#include "GeometryGenerator.h"

namespace ssw
{
	using namespace std;
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	MeshData GeometryGenerator::MakeBox(const float scale)
	{
		vector<Vector3> positions;
		vector<Vector3> colors;
		vector<Vector3> normals;
		vector<Vector2> texcoords;
		
		// 모든 면에서 같은 텍스처를 재사용하기 때문에 uv 좌표가 같음

		// 윗면
		positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
		positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
		positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
		positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
		colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
		colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
		colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
		colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
		texcoords.push_back(Vector2(0.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 1.0f));

		// 아랫면
		positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
		positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
		positions.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
		positions.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
		colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
		colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
		colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
		colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
		normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
		texcoords.push_back(Vector2(0.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 1.0f));

		// 앞면
		positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
		positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
		positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
		positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
		colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
		colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
		colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
		colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
		texcoords.push_back(Vector2(0.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 1.0f));

		// 뒷면
		positions.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
		positions.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
		positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
		positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
		colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
		colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
		colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
		colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
		normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 1.0f));

		// 왼쪽
		positions.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
		positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
		positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
		positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
		colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
		colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
		colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
		colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
		normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
		texcoords.push_back(Vector2(0.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 1.0f));

		// 오른쪽
		positions.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
		positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
		positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
		positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
		colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
		colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
		colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
		colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
		normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
		normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
		texcoords.push_back(Vector2(0.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 0.0f));
		texcoords.push_back(Vector2(1.0f, 1.0f));
		texcoords.push_back(Vector2(0.0f, 1.0f));

		MeshData meshData;
		for (size_t i = 0; i < positions.size(); i++) {
			Vertex v;
			v.position = positions[i];
			v.normal = normals[i];
			v.texcoord = texcoords[i];
			meshData.vertices.push_back(v);
		}

		meshData.indices = {
			0,  1,  2,  0,  2,  3,  // 윗면
			4,  5,  6,  4,  6,  7,  // 아랫면
			8,  9,  10, 8,  10, 11, // 앞면
			12, 13, 14, 12, 14, 15, // 뒷면
			16, 17, 18, 16, 18, 19, // 왼쪽
			20, 21, 22, 20, 22, 23  // 오른쪽
		};

		return meshData;
	}

	MeshData GeometryGenerator::MakeCylinder(const float bottomRadius,
		const float topRadius, float height, int numSlices)
	{
		const float dTheta = -XM_2PI / float(numSlices);

		MeshData meshData;
		vector<Vertex>& vertices = meshData.vertices;

		// 하단 부분
		for (int i = 0; i <= numSlices; ++i)
		{
			Vertex v;
			v.position =
				Vector3::Transform(Vector3(bottomRadius, -0.5f * height, 0.0f),
					Matrix::CreateRotationY(dTheta * float(i)));

			v.normal = v.position - Vector3(0.0f, -0.5f * height, 0.0f);
			v.normal.Normalize();

			vertices.push_back(v);
		}

		// 상단 부분
		for (int i = 0; i <= numSlices; ++i)
		{
			Vertex v;
			v.position =
				Vector3::Transform(Vector3(topRadius, 0.5f * height, 0.0f),
					Matrix::CreateRotationY(dTheta * float(i)));
			v.normal = v.position - Vector3(0.0f, 0.5f * height, 0.0f);
			v.normal.Normalize();

			vertices.push_back(v);
		}

		vector<uint32_t>& indices = meshData.indices;

		for (int i = 0; i < numSlices; ++i)
		{
			indices.push_back(i);
			indices.push_back(i + numSlices + 1);
			indices.push_back(i + 1 + numSlices + 1);

			indices.push_back(i);
			indices.push_back(i + 1 + numSlices + 1);
			indices.push_back(i + 1);
		}

		return meshData;
	}

	MeshData GeometryGenerator::MakeSphere(const float radius, const int numSlices, const int numStacks)
	{
		const float dTheta = -XM_2PI / float(numSlices);
		const float dPhi = -XM_PI / float(numStacks); // 세로 방향 구현 목적

		MeshData meshData;

		vector<Vertex>& vertices = meshData.vertices;

		for (int j = 0; j <= numStacks; ++j)
		{
			Vector3 stackStartPoint = Vector3::Transform(Vector3(0.0f, -radius, 0.0f),
				Matrix::CreateRotationZ(dPhi * j));

			for (int i = 0; i <= numSlices; ++i)
			{
				Vertex v;
				v.position = Vector3::Transform(stackStartPoint, Matrix::CreateRotationY(dTheta * float(i)));
				
				v.normal = v.position;
				v.normal.Normalize();
				v.texcoord = Vector2(float(i) / numSlices, 1.0f - float(j) / numStacks);

				vertices.push_back(v);
			}
		}

		vector<uint32_t>& indices = meshData.indices;

		for (int j = 0; j < numStacks; ++j)
		{
			const int offset = (numSlices + 1) * j;

			for (int i = 0; i < numSlices; ++i)
			{
				indices.push_back(offset + i);
				indices.push_back(offset + i + numSlices + 1);
				indices.push_back(offset + i + 1 + numSlices + 1);

				indices.push_back(offset + i);
				indices.push_back(offset + i + 1 + numSlices + 1);
				indices.push_back(offset + i + 1);
			}
		}

		return meshData;
	}
}