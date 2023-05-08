#pragma once

#include "hitable.hpp"
#include "hitablelist.hpp"
#include "aabb.hpp"
#include <vector>

class BVHNode : public Hitable
{
public:
    BVHNode() {}
    BVHNode(HitableList& list, float time0, float time1)
        : BVHNode(list.objects, 0, list.objects.size(), time0, time1)
    {}

    BVHNode(std::vector<Hitable*>& objects, int start, int end, float time0, float time1);

    virtual bool Hit(const Ray& r, float t_min, float t_max, HitInfo& rec) override;
    virtual bool BoundingBox(float time0, float time1, AABB& bbox) const override;
    
    Hitable* left;
    Hitable* right;
    AABB box;
};
