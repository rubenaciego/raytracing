#include "ray.hpp"
#include <cstdlib>

Vector3 randomUnitSphere()
{
    Vector3 p;

    do
    {
        p = Vector3(drand48(), drand48(), drand48()) * 2.0f - Vector3::ONE;

    } while (p.LengthSq() >= 1.0f);

    return p;
}

Vector3 randomUnitDisk()
{
    Vector3 p;

    do
    {
        p = Vector3(drand48(), drand48(), 0) * 2.0f - Vector3(1, 1, 0);

    } while (p.LengthSq() >= 1.0f);

    return p;
}

Ray::Ray(const Vector3& orgn, const Vector3& dir, float t) : origin(orgn), direction(dir), time(t)
{
}

Vector3 Ray::Point(float t) const
{
    return origin + direction * t;
}
