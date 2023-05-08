#include "lambertian.hpp"
#include <cstdlib>

Lambertian::Lambertian(const Vector3& a)
{
    texture = new SolidColor(a);
}

Lambertian::Lambertian(TextureRT* tex) : texture(tex)
{
}

Lambertian::~Lambertian()
{
    delete texture;
}

bool Lambertian::Scatter(const Ray& incident,
    const HitInfo& hit, Vector3& atten, Ray& scattered) const
{
    Vector3 targetDir = hit.normal + randomUnitSphere().Normalized();
    scattered = Ray(hit.position, targetDir, incident.time);
    atten = texture->Sample(hit.u, hit.v, hit.position);

    return true;
}
