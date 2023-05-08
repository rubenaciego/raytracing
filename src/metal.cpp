#include "metal.hpp"

Metal::Metal(const Vector3& a, float fuzz) : albedo(a), fuzz(fuzz)
{
}

bool Metal::Scatter(const Ray& incident,
    const HitInfo& hit, Vector3& atten, Ray& scattered) const
{
    Vector3 reflected = incident.direction.Normalized().Reflect(hit.normal);
    scattered = Ray(hit.position, reflected + randomUnitSphere().Normalized() * fuzz, incident.time);
    atten = albedo;

    return reflected.Dot(hit.normal) > 0;
}
