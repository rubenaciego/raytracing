#pragma once

#include "texturert.hpp"

int* GenerateUniformPerm(int n);

class PerlinNoise
{
public:
    PerlinNoise(int points);
    ~PerlinNoise();

    float Noise(const Vector3& p) const;

private:
    float* data;
    int* permx;
    int* permy;
    int* permz;
    int pointcount;
};

class NoiseTexture : public TextureRT
{
public:
    NoiseTexture(float f = 1.0f);

    virtual Vector3 Sample(float u, float v, const Vector3& p) const override;

private:
    PerlinNoise noise;
    float freq;
};
