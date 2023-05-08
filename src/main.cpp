#include "core/window.hpp"
#include "testScene.hpp"
#include <chrono>
#include <iostream>

extern const int WINDOW_WIDTH = 1280;
extern const int WINDOW_HEIGHT = 720;
Window* window;

int main(int argc, const char* argv[])
{
    window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f;
    TestScene* testScene = new TestScene;
    
    while (!window->shouldClose())
    {
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        t1 = t2;
        deltaTime = delta.count();

        testScene->update(deltaTime);

        window->bindFrameBuffer();
        testScene->render();
        window->swapBuffers();
        window->pollEvents();
    }

    delete testScene;
    delete window;

    return 0;
}
