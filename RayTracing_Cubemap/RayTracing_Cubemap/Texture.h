#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace ssw
{
	class Texture
	{
	public:
		int width;
		int height;
		int channels;
		std::vector<uint8_t> image;

		Texture(const std::string& filename);
		Texture(const int& width, const int& height, const std::vector<glm::vec3>& pixels);

		// 가장자리 이상일 경우 직전 픽셀 색 사용
		glm::vec3 GetClamped(int i, int j)
		{
			i = glm::clamp(i, 0, width - 1);
			j = glm::clamp(j, 0, height - 1);

			const float r = image[(i + width * j) * channels + 0] / 255.0f;
			const float g = image[(i + width * j) * channels + 1] / 255.0f;
			const float b = image[(i + width * j) * channels + 2] / 255.0f;

			return glm::vec3(r, g, b);
		}

		// 가장자리 이상일 경우 텍스처 반복
		glm::vec3 GetWrapped(int i, int j)
		{
			i %= width;
			j %= height;

			if (i < 0)
			{
				i += width;
			}

			if (j < 0)
			{
				j += height;
			}

			const float r = image[(i + width * j) * channels + 0] / 255.0f;
			const float g = image[(i + width * j) * channels + 1] / 255.0f;
			const float b = image[(i + width * j) * channels + 2] / 255.0f;

			return glm::vec3(r, g, b);
		}

		// 보간 연산
		glm::vec3 InterpolateBilinear(
			const float& dx,
			const float& dy,
			const glm::vec3& c00,
			const glm::vec3& c10,
			const glm::vec3& c01,
			const glm::vec3& c11)
		{
			glm::vec3 a = c00 * (1.0f - dx) + c10 * dx;
			glm::vec3 b = c01 * (1.0f - dx) + c11 * dx;
			return a * (1.0f - dy) + b * dy;
		}

		// 가까운 1픽셀 색 사용
		glm::vec3 SamplePoint(const glm::vec2 &uv)
		{
			glm::vec2 xy = uv * glm::vec2(width, height) - glm::vec2(0.5f);
			xy += glm::vec2(0.5f);

			int i = int(xy.x);
			int j = int(xy.y);

			return GetWrapped(i, j);
		}

		// 주변 4픽셀 색 보간
		glm::vec3 SampleLinear(const glm::vec2 &uv)
		{

			const glm::vec2 xy = uv * glm::vec2(width, height) - glm::vec2(0.5f);
			const int i = int(floor(xy.x));
			const int j = int(floor(xy.y));
			const float dx = xy.x - float(i);
			const float dy = xy.y - float(j);

			return InterpolateBilinear(dx, dy, GetWrapped(i, j), GetWrapped(i + 1, j), GetWrapped(i, j + 1), GetWrapped(i + 1, j + 1));
		}

		glm::vec3 SampleLinearClamped(const glm::vec2& uv)
		{
			const glm::vec2 xy = uv * glm::vec2(width, height) - glm::vec2(0.5f);
			const int i = int(floor(xy.x));
			const int j = int(floor(xy.y));
			const float dx = xy.x - float(i);
			const float dy = xy.y - float(j);
			return InterpolateBilinear(dx, dy, GetClamped(i, j), GetClamped(i + 1, j), GetClamped(i, j + 1), GetClamped(i + 1, j + 1));
		}

	};
}