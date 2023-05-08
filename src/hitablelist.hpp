#pragma once

#include "hitable.hpp"
#include <vector>

class HitableList : public Hitable
{
public:
    virtual bool Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit) override;
    virtual bool BoundingBox(float t0, float t1, AABB& bbox) const override;

    virtual ~HitableList();

    std::vector<Hitable*> objects;
};
