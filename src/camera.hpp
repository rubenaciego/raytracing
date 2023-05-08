#pragma once

#include "vector3.hpp"
#include "ray.hpp"

class Camera
{
public:
    Camera(float aperture, float focusDist, float height, float depth,
        const Vector3& position, const Vector3& point, const Vector3& upvec, float t0, float t1);

    Ray GetRay(float u, float v) const;

    Vector3 origin;
    Vector3 leftBottom;
    Vector3 horizontal;
    Vector3 vertical;

    Vector3 right;
    Vector3 up;
    Vector3 forward;

    float lensRadius;
    float time0;
    float time1;
};
