#pragma once

#include "texturert.hpp"
#include <string>

struct pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Image : public TextureRT
{
public:
    Image(const std::string& path);
    Image(int w, int h, pixel* imgdata);
    virtual ~Image();

    virtual Vector3 Sample(float u, float v, const Vector3& p) const override;

    int width;
    int height;

    pixel* data;
};
