#pragma once

#include "material.hpp"
#include "texturert.hpp"

class Lambertian : public Material
{
public:
    Lambertian(const Vector3& a);
    Lambertian(TextureRT* tex);
    virtual ~Lambertian();

    virtual bool Scatter(const Ray& incident,
        const HitInfo& hit, Vector3& atten, Ray& scattered) const override;

    TextureRT* texture;
};
