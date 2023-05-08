#include "bvhnode.hpp"
#include <random>
#include <iostream>
#include <algorithm>

BVHNode::BVHNode(std::vector<Hitable*>& objects, int start, int end, float time0, float time1)
{
    int objectnum = end - start;
    int axis = (int)(drand48() * 3.0);

    auto comparator = [axis, time0, time1](Hitable* a, Hitable* b) {
        AABB ba, bb;
        a->BoundingBox(time0, time1, ba);
        b->BoundingBox(time0, time1, bb);

        return ba.minimum[axis] < bb.minimum[axis];
    };

    if (objectnum == 1)
    {
        right = left = objects[start];
    }
    else if (objectnum == 2)
    {
        left = objects[start];
        right = objects[start + 1];

        if (comparator(right, left)) std::swap(right, left);
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        int mid = start + objectnum / 2;

        left = new BVHNode(objects, start, mid, time0, time1);
        right = new BVHNode(objects, mid, end, time0, time1);
    }

    AABB bleft, bright;

    if (!(left->BoundingBox(time0, time1, bleft) && right->BoundingBox(time0, time1, bright)))
        std::cerr << "Error building bounding boxes" << std::endl;

    box = SurroundingBox(bleft, bright);
}

bool BVHNode::Hit(const Ray& r, float t_min, float t_max, HitInfo& rec)
{
    if (!box.hit(r, t_min, t_max)) return false;

    bool hleft = left->Hit(r, t_min, t_max, rec);
    bool hright = right->Hit(r, t_min, hleft ? rec.t : t_max, rec);

    return hleft || hright;
}

bool BVHNode::BoundingBox(float time0, float time1, AABB& bbox) const
{
    bbox = box;
    return true;
}
