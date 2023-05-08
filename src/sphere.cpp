#include "sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector3& c, float r, Material* mat) : center(c), radius(r), material(mat)
{
}

bool Sphere::Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit)
{
    Vector3 oc = ray.origin - center;
    // Quadratic equation
    float a = ray.direction.Dot(ray.direction);
    float b = 2.0f * oc.Dot(ray.direction);
    float c = oc.Dot(oc) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;
    
    if (discriminant > 0.0f)
    {
        float temp = (-b - sqrtf(discriminant)) / (2.0f * a);
        bool found = false;

        if (temp < tmax && temp > tmin)
            found = true;
        else
        {
            temp = (-b + sqrtf(discriminant)) / (2.0f * a);
            if (temp < tmax && temp > tmin)
                found = true;
        }

        if (found)
        {
            hit.t = temp;
            hit.position = ray.Point(temp);
            hit.material = material;
            hit.set_face_normal(ray, (hit.position - center) / radius);
            GetSphereUV(hit.normal, hit.u, hit.v);

            return true;
        }
    }

    return false;
}

bool Sphere::BoundingBox(float t0, float t1, AABB& bbox) const
{
    bbox = AABB(center - Vector3::ONE * radius, center + Vector3::ONE * radius);
    return true;
}

void Sphere::GetSphereUV(const Vector3& p, float& u, float& v)
{
    float theta = acosf(-p.y);
    float phi = atan2f(-p.z, -p.x) + M_PI;

    u = phi / (M_PI * 2.0f);
    v = theta / M_PI;
}
