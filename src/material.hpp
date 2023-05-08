#pragma once

#include <cmath>
#include "ray.hpp"
#include "hitable.hpp"

Vector3 randomUnitSphere();

class Material
{
public:
    virtual bool Scatter(const Ray& incident,
        const HitInfo& hit, Vector3& atten, Ray& scattered) const = 0;
    virtual ~Material() = default;
};

double schlick(double cosine, double ref_idx);
