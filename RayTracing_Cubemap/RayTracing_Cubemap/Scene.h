#pragma once

#include "Object.h"
#include "Light.h"
#include "Texture.h"
#include "Sphere.h"
#include "Square.h"
#include "Cubemap.h"

#include <vector>
#include <memory>
#include <iostream>

namespace ssw
{
	class Scene
	{
	public:
		std::vector<std::shared_ptr<Object>> objects;
		Light light;
		std::shared_ptr<Cubemap> cubemap;

		void Setup()
		{
			auto transparentSphere = std::make_shared<Sphere>(glm::vec3(1.3f, -0.3f, 1.5f), 0.7f);

			transparentSphere->ambient = glm::vec3(0.2f);
			transparentSphere->diffuse = glm::vec3(0.0f, 0.0f, 0.1f);
			transparentSphere->specular = glm::vec3(0.0f);
			transparentSphere->alpha = 50.0f;
			transparentSphere->reflection = 0.0f;
			transparentSphere->transparency = 1.0f;

			objects.push_back(transparentSphere);

			auto groundTexture = std::make_shared<Texture>("..\\Cubemap_Images\\Stones.jpg");
			
			// uv 범위를 0.0 ~ 1.0이 아닌 0.0 ~ 3.0 같이 설정하면 반복이 발생함 - GetWrapped
			auto ground = std::make_shared<Square>(glm::vec3(-10.0f, -1.5f, 0.0f), glm::vec3(-10.0f, -1.5f, 10.0f), glm::vec3(10.0f, -1.5f, 10.0f), glm::vec3(10.0f, -1.5f, 0.0f),
				glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 0.0f), glm::vec2(3.0f, 3.0f), glm::vec2(0.0f, 3.0f));

			ground->ambient = glm::vec3(0.8f);
			ground->diffuse = glm::vec3(0.8f);
			ground->specular = glm::vec3(1.0f);
			ground->alpha = 10.0f;
			ground->reflection = 0.0f;
			ground->ambientTexture = groundTexture;
			ground->diffuseTexture = groundTexture;

			//objects.push_back(ground);

			cubemap = std::make_shared<Cubemap>();
			cubemap->positiveX_Texture = std::make_shared<Texture>("..\\Cubemap_Images\\BlueSunset_Left+X.png");
			cubemap->negativeX_Texture = std::make_shared<Texture>("..\\Cubemap_Images\\BlueSunset_Right-X.png");
			cubemap->positiveY_Texture = std::make_shared<Texture>("..\\Cubemap_Images\\BlueSunset_Up+Y.png");
			cubemap->negativeY_Texture = std::make_shared<Texture>("..\\Cubemap_Images\\BlueSunset_Down-Y.png");
			cubemap->positiveZ_Texture = std::make_shared<Texture>("..\\Cubemap_Images\\BlueSunset_Front+Z.png");
			cubemap->negativeZ_Texture = std::make_shared<Texture>("..\\Cubemap_Images\\BlueSunset_Back-Z.png");

			light = Light{ {0.0f, 0.3f, -0.5f } };
		}
	};
}