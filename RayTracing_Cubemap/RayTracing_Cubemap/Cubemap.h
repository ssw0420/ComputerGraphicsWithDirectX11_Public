#pragma once

#include "Texture.h"
#include <memory>
#include <glm/glm.hpp>

namespace ssw
{
	class Cubemap
	{
	public:
		std::shared_ptr<Texture> positiveX_Texture; // +X
		std::shared_ptr<Texture> negativeX_Texture; // -X

		std::shared_ptr<Texture> positiveY_Texture; // +Y
		std::shared_ptr<Texture> negativeY_Texture; // -Y

		std::shared_ptr<Texture> positiveZ_Texture; // +Z
		std::shared_ptr<Texture> negativeZ_Texture; // -Z

		glm::vec3 Sample(const glm::vec3& dir) const
		{
			const glm::vec3 absDir = glm::abs(dir);

			float faceU, faceV;
			std::shared_ptr<Texture> face;

            if (absDir.x >= absDir.y && absDir.x >= absDir.z)   // X축이 최대 -> 좌/우 면
            {
                if (dir.x > 0.0f)
                {
                    face = positiveX_Texture;
                    faceU = -dir.z / absDir.x;
                    faceV = -dir.y / absDir.x;
                }
                else
                {
                    face = negativeX_Texture;
                    faceU = dir.z / absDir.x;
                    faceV = -dir.y / absDir.x;
                }
            }
            else if (absDir.y >= absDir.z)                       // Y축이 최대 -> 상/하 면
            {
                if (dir.y > 0.0f)
                {
                    face = positiveY_Texture;
                    faceU = dir.x / absDir.y;
                    faceV = dir.z / absDir.y;
                }
                else
                {
                    face = negativeY_Texture;
                    faceU = dir.x / absDir.y;
                    faceV = -dir.z / absDir.y;
                }
            }
            else                                                 // Z축이 최대 -> 앞/뒤 면
            {
                if (dir.z > 0.0f)
                {
                    face = positiveZ_Texture;
                    faceU = dir.x / absDir.z;
                    faceV = -dir.y / absDir.z;
                }
                else
                {
                    face = negativeZ_Texture;
                    faceU = -dir.x / absDir.z;
                    faceV = -dir.y / absDir.z;
                }
            }

            // 면 좌표 [-1, 1] → 텍스처 uv [0, 1] 로 변환
            const glm::vec2 uv = (glm::vec2(faceU, faceV) + 1.0f) * 0.5f;
            return face->SampleLinearClamped(uv);
		}
	};
}