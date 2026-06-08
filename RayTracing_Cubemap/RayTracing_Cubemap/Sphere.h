#pragma once
#include "Object.h"

namespace ssw
{
	class Sphere : public Object
	{
	public:
		glm::vec3 center;
		float radius;

		Sphere(const glm::vec3& center, const float radius, const glm::vec3& color = glm::vec3(1.0f))
			: center(center), radius(radius), Object(color)
		{
		}

        Hit CheckRayCollision(Ray& ray)
        {
            Hit hit = Hit{ -1.0f, glm::vec3(0.0f), glm::vec3(0.0f) };

            const float b = 2.0f * glm::dot(ray.dir, ray.start - this->center);
            const float c = dot(ray.start - this->center, ray.start - this->center) - this->radius * this->radius;

            const float det = b * b - 4.0f * c;
            if (det >= 0.0f)
            {
                const float d1 = (-b - sqrt(det)) / 2.0f;
                const float d2 = (-b + sqrt(det)) / 2.0f;
                hit.distance = glm::min(d1, d2);

                // 물체 안에서 다시 밖으로 나가면서 충돌 가능
                if (hit.distance < 0.0f)
                    hit.distance = glm::max(d1, d2);

                hit.point = ray.start + ray.dir * hit.distance;
                hit.normal = glm::normalize(hit.point - this->center);
            }

            return hit;
        }
	};
}