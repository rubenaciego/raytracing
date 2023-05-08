#pragma once

#include "vector3.hpp"
#include "ray.hpp"
#include "aabb.hpp"

class Material;

struct HitInfo
{
    float t;
    Vector3 position;
    Vector3 normal;
    float u;
    float v;
    Material* material;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vector3& outward_normal)
    {
        front_face = r.direction.Dot(outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal * -1.0f;
    }
};

class Hitable
{
public:
    virtual bool Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit) = 0;
    virtual bool BoundingBox(float t0, float t1, AABB& bbox) const = 0;
    virtual ~Hitable() = default;
};
