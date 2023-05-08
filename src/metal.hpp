#pragma once

#include "material.hpp"

class Metal : public Material
{
public:
    Metal(const Vector3& a, float fuzz);
    
    virtual bool Scatter(const Ray& incident,
        const HitInfo& hit, Vector3& atten, Ray& scattered) const override;

    Vector3 albedo;
    float fuzz;
};
