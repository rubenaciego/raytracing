#pragma once

#include "vector3.hpp"

Vector3 randomUnitDisk();
Vector3 randomUnitSphere();

class Ray
{
public:
    Ray(const Vector3& orgn, const Vector3& dir, float t = 0.0f);
    
    Vector3 Point(float t) const;

    Vector3 origin;
    Vector3 direction;
    float time;
};
