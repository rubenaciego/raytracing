#include "perlinnoise.hpp"
#include <random>

int* GenerateUniformPerm(int n)
{
    int* res = new int[n];

    for (int i = 0; i < n; ++i)
    {
        res[i] = i;

        int swapindex = (int)(drand48() * (double)(i + 1));
        std::swap(res[i], res[swapindex]);
    }

    return res;
}

PerlinNoise::PerlinNoise(int points) : pointcount(points)
{
    data = new float[points];

    for (int i = 0; i < points; ++i)
        data[i] = (float)drand48();

    permx = GenerateUniformPerm(points);
    permy = GenerateUniformPerm(points);
    permz = GenerateUniformPerm(points);
}

PerlinNoise::~PerlinNoise()
{
    delete[] data;
    delete[] permx;
    delete[] permy;
    delete[] permz;
}

float PerlinNoise::Noise(const Vector3& p) const
{
    int i = floor(p.x);
    int j = floor(p.y);
    int k = floor(p.z);
    float u = p.x - i;
    float v = p.y - j;
    float w = p.z - k;

    // Hermitian smooth
    u = u*u*(3-2*u);
    v = v*v*(3-2*v);
    w = w*w*(3-2*w);

    float res = 0.0f;

    // Trilinear filterning
    for (int dx = 0; dx < 2; ++dx)
    {
        for (int dy = 0; dy < 2; ++dy)
        {
            for (int dz = 0; dz < 2; ++dz)
            {
                int index = (permx[abs((i + dx)) % pointcount] ^
                    permy[abs((j + dy)) % pointcount] ^ permz[abs((k + dz)) % pointcount]) % pointcount;

                float sampleval = data[index];
                res += ((float)dx * u + (1 - (float)dx) * (1 - u)) *
                    ((float)dy * v + (1 - (float)dy) * (1 - v)) *
                    ((float)dz * w + (1 - (float)dz) * (1 - w)) * sampleval;
            }
        }
    }

    return res;
}

NoiseTexture::NoiseTexture(float f) : noise(256), freq(f)
{
}

Vector3 NoiseTexture::Sample(float u, float v, const Vector3& p) const
{
    return Vector3::ONE * noise.Noise(p * freq);
}
