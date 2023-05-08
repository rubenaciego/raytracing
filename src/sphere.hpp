#pragma once

#include "hitable.hpp"

class Sphere : public Hitable
{
public:
    Sphere(const Vector3& c, float r, Material* mat);
    
    virtual bool Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit) override;
    virtual bool BoundingBox(float t0, float t1, AABB& bbox) const override;

    static void GetSphereUV(const Vector3& p, float& u, float& v);

    Vector3 center;
    float radius;
    Material* material;
};
