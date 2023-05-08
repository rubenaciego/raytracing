#pragma once

#include "core/core.hpp"
#include <string>

class Window
{
private:
    int width;
    int height;
    glm::vec2 mousePosition;
    GLFWwindow* window;

    static void resizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

public:
    Window(int width, int height, const std::string& name);
    ~Window();

    int getKey(int key) const;
    void pollEvents() const;
    void swapBuffers() const;
    void close() const;
    void bindFrameBuffer() const;
    bool shouldClose() const;
    glm::vec2 getMousePosition() const;
    int getWidth() const;
    int getHeight() const;
};
