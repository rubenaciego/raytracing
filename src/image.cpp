#include "image.hpp"
#include <cmath>
#include <stb_image/stb_image.h>

Image::Image(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);
    int channels;
    data = (pixel*)stbi_load(path.c_str(), &width, &height, &channels, 0);
}

Image::Image(int w, int h, pixel* imgdata) : width(w), height(h), data(imgdata)
{
}

Image::~Image()
{
    delete data;
}

Vector3 Image::Sample(float u, float v, const Vector3& p) const
{
    float unused;
    u = modff(u, &unused);
    v = modff(v, &unused);
    int ucoord = u * width;
    int vcoord = v * height;

    pixel pix = data[ucoord + width * vcoord];
    float div = 1.0f / 255.0f;

    return Vector3((float)pix.r * div, (float)pix.g * div, (float)pix.b * div);
}
