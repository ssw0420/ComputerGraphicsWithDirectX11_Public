#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace ssw
{
	class Object;

	class Hit
	{
	public:
		float distance;
		glm::vec3 point; // 충돌 위치
		glm::vec3 normal; // 충돌 위치에서 표면의 노말 벡터
		glm::vec2 uv; // 텍스처 좌표

		// pointer만 가질 때는 객체 자체의 크기를 알 필요가 없으므로 include가 필요 없음
		// 객체를 별도로 만들 때나 이 포인터를 기반으로 멤버 접근을 할 때는 include 해줘야 함
		// 여기선 Object가 있다는 걸 알리기만 하고, 이걸 실제 RayTracer.h에서 쓸 때 include는 따로 해줘야 함
		std::shared_ptr<Object> obj; // 물체 정보
	};
}
