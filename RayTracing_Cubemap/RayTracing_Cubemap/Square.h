#pragma once

#include "Triangle.h"

namespace ssw
{
    class Square : public Object
    {
    public:
        Triangle triangle1, triangle2;

        Square(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec2 uv0 = glm::vec2(0.0f), glm::vec2 uv1 = glm::vec2(0.0f), glm::vec2 uv2 = glm::vec2(0.0f), glm::vec2 uv3 = glm::vec2(0.0f))
            : triangle1(v0, v1, v2), triangle2(v0, v2, v3)
        {
            triangle1.uv0 = uv0;
            triangle1.uv1 = uv1;
            triangle1.uv2 = uv2;

            triangle2.uv0 = uv0;
            triangle2.uv1 = uv2;
            triangle2.uv2 = uv3;
        }

        virtual Hit CheckRayCollision(Ray& ray)
        {
            auto hit1 = triangle1.CheckRayCollision(ray);
            auto hit2 = triangle2.CheckRayCollision(ray);

            if (hit1.distance >= 0.0f && hit2.distance >= 0.0f)
            {
                return hit1.distance < hit2.distance ? hit1 : hit2;
            }
            else if (hit1.distance >= 0.0f)
            {
                return hit1;
            }
            else
            {
                return hit2;
            }
        }
    };
}
