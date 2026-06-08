#pragma once

#include "Ray.h"
#include "Light.h"
#include "Object.h"
#include "Scene.h"

#include <vector>


namespace ssw
{
	class RayTracer
	{
	public:
		int width, height;

		RayTracer(const int& width, const int& height)
			: width(width), height(height)
		{
		}

		Hit FindClosestCollision(const Scene& scene, Ray& ray)
		{
			float closestDistance = 1000.0f; // infinite
			Hit closestHit = Hit{ -1.0, glm::vec3(0.0), glm::vec3(0.0) }; // distance, point, normal

			for (int l = 0; l < scene.objects.size(); ++l)
			{
				auto hit = scene.objects[l]->CheckRayCollision(ray);

				if (hit.distance >= 0.0f)
				{
					if (hit.distance < closestDistance)
					{
						closestDistance = hit.distance;
						closestHit = hit;
						closestHit.obj = scene.objects[l];
						closestHit.uv = hit.uv;
					}
				}
			}

			return closestHit;
		}

		glm::vec3 traceRay(const Scene& scene, Ray& ray, const int recurseLevel)
		{
			if (recurseLevel < 0) return glm::vec3(0.0f);

			// Render first hit
			const auto hit = FindClosestCollision(scene, ray);

			if (hit.distance >= 0.0f)
			{
				glm::vec3 color(0.0f);

				// Diffuse
				const glm::vec3 dirToLight = glm::normalize(scene.light.pos - hit.point);
				glm::vec3 phongColor(0.0f);
				const float diffuse = glm::max(glm::dot(hit.normal, dirToLight), 0.0f);

				// Specular
				const glm::vec3 reflectDirection = hit.normal * 2.0f * glm::dot(dirToLight, hit.normal) - dirToLight;
				const float specular = glm::pow(glm::max(glm::dot(-ray.dir, reflectDirection), 0.0f), hit.obj->alpha);

				// phongColor

				if (hit.obj->ambientTexture)
				{
					phongColor += hit.obj->ambient * hit.obj->ambientTexture->SampleLinear(hit.uv);
				}
				else // 텍스처가 없는 경우
				{
					phongColor += hit.obj->ambient;
				}

				if (hit.obj->diffuseTexture)
				{
					phongColor += diffuse * hit.obj->diffuse * hit.obj->diffuseTexture->SampleLinear(hit.uv);
				}
				else // 텍스처가 없는 경우
				{
					phongColor += diffuse * hit.obj->diffuse;
				}

				phongColor += hit.obj->specular * specular;

				color += phongColor * (1.0f - hit.obj->reflection - hit.obj->transparency);

				if (hit.obj->reflection)
				{
					const auto reflectedDirection = glm::normalize(2.0f * hit.normal * dot(-ray.dir, hit.normal) + ray.dir);
					Ray reflection_ray{ hit.point + reflectedDirection * 1e-4f, reflectedDirection }; // add a small vector to avoid numerical issue

					color += traceRay(scene, reflection_ray, recurseLevel - 1) * hit.obj->reflection;
				}

				if (hit.obj->transparency)
				{
					const float ior = 1.5f; // Index of refraction (유리: 1.5, 물: 1.3)

					float eta; // sinTheta1 / sinTheta2
					glm::vec3 normal;

					if (glm::dot(ray.dir, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
					{
						eta = ior;
						normal = hit.normal;
					}
					else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
					{
						eta = 1.0f / ior;
						normal = -hit.normal;
					}

					const float cosTheta1 = glm::dot(normal, -ray.dir);
					const float sinTheta1 = sqrt(1.0f - cosTheta1 * cosTheta1);
					const float sinTheta2 = sinTheta1 / eta;
					const float cosTheta2 = sqrt(1.0f - sinTheta2 * sinTheta2);

					const glm::vec3 m = glm::normalize(dot(normal, -ray.dir) * normal + ray.dir);
					const glm::vec3 a = -(normal * cosTheta2);
					const glm::vec3 b = m * sinTheta2;
					const glm::vec3 refractedDirection = glm::normalize(a + b);

					Ray refractionRay{ hit.point + refractedDirection * 1e-4f, refractedDirection };

					color += traceRay(scene, refractionRay, recurseLevel - 1) * hit.obj->transparency;
				}

				return color;
			}

			return scene.cubemap ? scene.cubemap->Sample(ray.dir) : glm::vec3(0.0f);
		}


		void Render(const Scene& scene, std::vector<glm::vec4>& pixels)
		{
			std::fill(pixels.begin(), pixels.end(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			const glm::vec3 eyePos(0.0f, 0.0f, -1.5f);

			// OpenMP - 루프를 여러 CPU코어에 분배
#pragma omp parallel for
			for (int j = 0; j < height; j++)
				for (int i = 0; i < width; i++)
				{
					const glm::vec3 pixelPosWorld = TransformScreenToWorld(glm::vec2(i, j));
					Ray pixelRay{ pixelPosWorld, glm::normalize(pixelPosWorld - eyePos) };
					pixels[i + width * j] = glm::vec4(glm::clamp(traceRay(scene, pixelRay, 5), 0.0f, 1.0f), 1.0f);
				}
		}

		glm::vec3 TransformScreenToWorld(glm::vec2 posScreen)
		{
			const float xScale = 2.0f / this->width;
			const float yScale = 2.0f / this->height;
			const float aspect = float(this->width) / this->height;

			// 3차원 공간으로 확장 (z좌표는 0.0)
			return glm::vec3((posScreen.x * xScale - 1.0f) * aspect, -posScreen.y * yScale + 1.0f, 0.0f);
		}
	};
}