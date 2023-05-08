#include "testScene.hpp"
#include <iostream>
#include <cfloat>
#include <list>
#include <cstdlib>
#include <cmath>
#include "vector3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "movingsphere.hpp"
#include "camera.hpp"
#include "hitable.hpp"
#include "metal.hpp"
#include "lambertian.hpp"
#include "dielectric.hpp"

#define MAX_BOUNCES 5

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern Window* window;

Vector3 getColor(Ray& ray, Hitable& world, int depth)
{
    HitInfo nearest;
    bool hit = world.Hit(ray, 0.001f, std::numeric_limits<float>::infinity(), nearest);

    if (hit)
    {
        Ray scattered(Vector3::ZERO, Vector3::ZERO);
        Vector3 attenuation;

        if (depth < MAX_BOUNCES && nearest.material->Scatter(ray, nearest, attenuation, scattered))
            return attenuation * getColor(scattered, world, depth + 1);
        else
            return Vector3::ZERO;
    }
    else
    {
        // Background color
        Vector3 bg(0.5f, 0.7f, 1.0f);
        Vector3 dir = ray.direction.Normalized();
        float factor = 0.5f * (dir.y + 1.0f);

        return Vector3::ONE.Lerp(bg, factor);
    }
}

TestScene::TestScene() : shader("shaders/tex2d.glsl"),
    tex(nullptr, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB),
    quad(glm::vec2(-1, -1), glm::vec2(2, 2)),
    camera(0.1f, 10.0f, 0.349f, 16.0f / 9.0f, Vector3(13,2,3), Vector3(0,0,0), Vector3(0,1,0), 0, 1)
{
    float resScale = 0.75f;
    width = (int)(WINDOW_WIDTH * resScale);
    height = (int)(WINDOW_HEIGHT * resScale);
    pixelSamples = 20;

    frame = new pixel[width * height];

    //auto ground_material = new Lambertian(Vector3(0.5, 0.5, 0.5));
    auto ground_material = new Lambertian(new NoiseTexture(4));//CheckerTexture());
    world.objects.push_back(new Sphere(Vector3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = drand48();
            Vector3 center(a + 0.9*drand48(), 0.2, b + 0.9*drand48());

            if ((center - Vector3(4, 0.2, 0)).Length() > 0.9) {
                Material* sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Vector3(drand48(), drand48(), drand48()) * Vector3(drand48(), drand48(), drand48());
                    sphere_material = new Lambertian(albedo);
                    auto center2 = center + Vector3(0, drand48()*0.5f, 0);
                    world.objects.push_back(new MovingSphere(0.2, sphere_material, 0, center, 1, center2));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = (Vector3(drand48(), drand48(), drand48()) + Vector3::ONE) * 0.5f;
                    auto fuzz = drand48() * 0.5f;
                    sphere_material = new Metal(albedo, fuzz);
                    world.objects.push_back(new Sphere(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = new Dielectric(1.5);
                    world.objects.push_back(new Sphere(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = new Dielectric(1.5);
    world.objects.push_back(new Sphere(Vector3(0, 1, 0), 1.0, material1));

    auto material2 = new Lambertian(new Image("earthmap.jpg"));
    world.objects.push_back(new Sphere(Vector3(-4, 1, 0), 1.0, material2));

    auto material3 = new Metal(Vector3(0.7, 0.6, 0.5), 0.0);
    world.objects.push_back(new Sphere(Vector3(4, 1, 0), 1.0, material3));
    bvh = new BVHNode(world, 0.0f, 1.0f);
}

TestScene::~TestScene()
{
    delete bvh;
    delete[] frame;
}

void TestScene::update(float deltaTime)
{
    std::cout << deltaTime * 1000.0f << " ms " << 1.0f / deltaTime << " fps" << std::endl;

    float completed = 0;
    float total = width * height;

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector3 color = Vector3::ZERO;

            for (int i = 0; i < pixelSamples; ++i)
            {
                float u = (float)(x + drand48()) / width;
                float v = (float)(y + drand48()) / height;
                Ray ray = camera.GetRay(u, v);

                color += getColor(ray, *bvh, 0);
            }

            color /= (float)pixelSamples;
            // Gamma 2 correction
            color = Vector3(sqrtf(color.x), sqrtf(color.y), sqrtf(color.z));

            pixel p;
            p.r = (int)(color.x * 255.9f);
            p.g = (int)(color.y * 255.9f);
            p.b = (int)(color.z * 255.9f);

            //std::cout << (int)r << " " << (int)g << " " << (int)b << std::endl;
            frame[x + y * width] = p;

            completed += 1.0f;
        }

        std::cout << completed / total * 100.0f << "%" << std::endl;
    }

    tex.setData(frame, width, height, GL_RGB);
}

void TestScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    quad.bind();
    shader.bind();
    tex.bind(0);

    shader.setUniformInt("tex", 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
