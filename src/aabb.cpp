#include "aabb.hpp"
#include "math.h"

AABB::AABB(const Vector3& a, const Vector3& b) : minimum(a), maximum(b)
{
}

bool AABB::hit(const Ray& r, float tmin, float tmax) const
{
    for (int i = 0; i < 3; ++i)
    {
        float tin = (minimum[i] - r.origin[i]) / r.direction[i];
        float tout = (maximum[i] - r.origin[i]) / r.direction[i];

        float t0 = std::fmin(tin, tout);
        float t1 = std::fmax(tin, tout);

        tmin = std::fmax(t0, tmin);
        tmax = std::fmin(t1, tmax);

        if (tmin >= tmax) return false;
    }

    return true;
}

AABB SurroundingBox(const AABB& a, const AABB& b)
{
    AABB res(Vector3::ZERO, Vector3::ZERO);

    for (int i = 0; i < 3; ++i)
    {
        res.minimum[i] = std::fmin(a.minimum[i], b.minimum[i]);
        res.maximum[i] = std::fmax(a.maximum[i], b.maximum[i]);
    }

    return res;
}
