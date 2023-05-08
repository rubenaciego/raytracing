#pragma once

#include "vector3.hpp"
#include "ray.hpp"

class AABB
{
public:

    AABB(const Vector3& a = Vector3::ZERO, const Vector3& b = Vector3::ZERO);

    bool hit(const Ray& r, float tmin, float tmax) const;

    // AABB planes
    Vector3 minimum;
    Vector3 maximum;
};

AABB SurroundingBox(const AABB& a, const AABB& b);
