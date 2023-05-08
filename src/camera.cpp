#include "camera.hpp"
#include <cmath>
#include <iostream>

Camera::Camera(float aperture, float focusDist, float fov, float aspectRatio,
    const Vector3& position, const Vector3& point, const Vector3& upvec, float t0, float t1) : time0(t0), time1(t1)
{
    float h = tanf(fov / 2.0f);
    float height = 2.0f * h;
    float width = aspectRatio * height;

    forward = (point - position).Normalized();
    right = forward.Cross(upvec).Normalized();
    up = right.Cross(forward);

    origin = position;
    vertical = up * height * focusDist;
    horizontal = right * width * focusDist;
    leftBottom = origin - horizontal * 0.5f - vertical * 0.5f + forward * focusDist;
    lensRadius = aperture * 0.5f;
}

Ray Camera::GetRay(float u, float v) const
{
    Vector3 random = randomUnitDisk() * lensRadius;
    Vector3 lensOffset = right * random.x + up * random.y;

    float t = drand48();
    return Ray(origin + lensOffset, leftBottom + horizontal * u + vertical * v - origin - lensOffset, time0 * t + time1 * (1.0f - t));
}
