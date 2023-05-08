#pragma once

#include "vector3.hpp"

class TextureRT
{
public:
    virtual ~TextureRT() = default;
    virtual Vector3 Sample(float u, float v, const Vector3& p) const = 0;
};

class SolidColor : public TextureRT
{
public:
    SolidColor(const Vector3& c) : color(c)
    {
    }

    virtual Vector3 Sample(float u, float v, const Vector3& p) const override
    {
        return color;
    }

    Vector3 color;
};

class CheckerTexture : public TextureRT
{
    virtual Vector3 Sample(float u, float v, const Vector3& p) const override
    {
        bool color = false;

        for (int i = 0; i < 3; ++i)
        {
            if ((int)p[i] % 2) color = !color;
        }

        if (color) return Vector3::ZERO;
        else return Vector3::ONE;
    }
};
