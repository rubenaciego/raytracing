#include "core/core.hpp"
#include "core/window.hpp"
#include "render/render2D/quad.hpp"
#include "render/buffers/vertexArray.hpp"
#include "render/buffers/vertexBuffer.hpp"
#include "render/buffers/indexBuffer.hpp"
#include "render/shader.hpp"
#include "render/texture.hpp"
#include "render/buffers/frameBuffer.hpp"
#include "hitable.hpp"
#include "bvhnode.hpp"
#include "camera.hpp"
#include "hitablelist.hpp"
#include "perlinnoise.hpp"
#include "image.hpp"
#include <list>

class TestScene
{
private:
    Shader shader;
    Texture tex;

    Quad quad;

    int width;
    int height;
    int pixelSamples;
    
    Camera camera;

    pixel* frame;
    HitableList world;
    BVHNode* bvh;

public:
    TestScene();
    ~TestScene();

    void update(float deltaTime);
    void render();
};
