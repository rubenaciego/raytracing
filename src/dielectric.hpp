#pragma once

#include <cmath>
#include "material.hpp"

class Dielectric : public Material
{
    public:
        Dielectric(double ri) : ref_idx(ri) {}

        virtual bool Scatter(
            const Ray& r_in, const HitInfo& rec, Vector3& attenuation, Ray& scattered) const override
        {
            attenuation = Vector3(1.0, 1.0, 1.0);
            double etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;
            Vector3 unit_direction = r_in.direction.Normalized();

            float c = -rec.normal.Dot(unit_direction);
            double reflect_prob = schlick(c, etai_over_etat);

            if (etai_over_etat * sqrtf(1 - c*c) > 1.0f || drand48() < reflect_prob)
            {   
                Vector3 reflected = unit_direction.Reflect(rec.normal);
                scattered = Ray(rec.position, reflected, r_in.time);
            }
            else
            {
                Vector3 refracted = unit_direction.Refract(rec.normal, etai_over_etat);
                scattered = Ray(rec.position, refracted, r_in.time);
            }
            
            return true;
        }

        double ref_idx;
};
