#include "hitablelist.hpp"
#include <limits>

HitableList::~HitableList()
{
    for (Hitable* h : objects)
        delete h;
}

bool HitableList::Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit)
{
    bool res = false;
    float lastTime = std::numeric_limits<float>::infinity();

    for (Hitable* object : objects)
    {
        HitInfo info;
        bool h = object->Hit(ray, tmin, tmax, info);

        if (h)
        {
            res = true;

            if (info.t < lastTime)
            {
                hit = info;
                lastTime = hit.t;
            }
        }
    }

    return res;
}

bool HitableList::BoundingBox(float t0, float t1, AABB& bbox) const
{
    if (objects.empty()) return false;

    bool firstbox = true;

    for (Hitable* h : objects)
    {
        AABB temp;
        if (!h->BoundingBox(t0, t1, temp)) return false;
        
        if (firstbox) bbox = temp;
        else bbox = SurroundingBox(bbox, temp);

        firstbox = false;
    }

    return true;
}
