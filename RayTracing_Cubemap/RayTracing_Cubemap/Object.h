#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Ray.h"
#include "Hit.h"
#include "Texture.h"

namespace ssw
{

	class Object
	{
	public:
		glm::vec3 ambient = glm::vec3(0.0f);
		glm::vec3 diffuse = glm::vec3(0.0f);
		glm::vec3 specular = glm::vec3(0.0f);

		float alpha = 10.0f;
		float reflection = 0.0f;
		float transparency = 0.0f;

		std::shared_ptr<Texture> ambientTexture;
		std::shared_ptr<Texture> diffuseTexture;

		Object(const glm::vec3& color = { 1.0f, 1.0f, 1.0f })
			: ambient(color), diffuse(color), specular(color)
		{
		}

		virtual Hit CheckRayCollision(Ray& ray) = 0;
	};
}
