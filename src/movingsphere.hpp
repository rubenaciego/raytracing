#pragma once

#include "hitable.hpp"

class MovingSphere : public Hitable
{
public:
    MovingSphere(float r, Material* mat, float t0, const Vector3& c0, float t1, const Vector3& c1);
    
    Vector3 Center(float t);
    virtual bool Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit) override;
    virtual bool BoundingBox(float t0, float t1, AABB& bbox) const override;

    float radius;
    Material* material;
    float time0;
    float time1;
    Vector3 center0;
    Vector3 center1;
};
