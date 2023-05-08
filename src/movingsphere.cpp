#include "movingsphere.hpp"
#include "sphere.hpp"
#include <cmath>

MovingSphere::MovingSphere(float r, Material* mat,
    float t0, const Vector3& c0, float t1, const Vector3& c1) : radius(r), material(mat),
        time0(t0), time1(t1), center0(c0), center1(c1)
{
}

Vector3 MovingSphere::Center(float t)
{
    float h = (t - time0) / (time1 - time0);
    return center1 * h + center0 * (1.0f - h);
}

bool MovingSphere::Hit(const Ray& ray, float tmin, float tmax, HitInfo& hit)
{
    Vector3 center = Center(ray.time);
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
            Sphere::GetSphereUV(hit.normal, hit.u, hit.v);

            return true;
        }
    }

    return false;
}

bool MovingSphere::BoundingBox(float t0, float t1, AABB& bbox) const
{
    AABB box0(center0 - Vector3::ONE * radius, center0 + Vector3::ONE * radius);
    AABB box1(center1 - Vector3::ONE * radius, center1 + Vector3::ONE * radius);

    bbox = SurroundingBox(box0, box1);
    return true;
}
