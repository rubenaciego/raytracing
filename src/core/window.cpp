#include "window.hpp"

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
    Window* w = (Window*)glfwGetWindowUserPointer(window);
    w->width = width;
    w->height = height;

    glViewport(0, 0, width, height);
}

void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Window* w = (Window*)glfwGetWindowUserPointer(window);
    w->mousePosition.x = (float)xpos;
    w->mousePosition.y = (float)ypos;
}

Window::Window(int width, int height, const std::string& name) : width(width), height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    assert(window != nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    glViewport(0, 0, width, height);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

int Window::getKey(int key) const
{
    return glfwGetKey(window, key);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(window);
}

void Window::close() const
{
    glfwSetWindowShouldClose(window, true);
}

void Window::bindFrameBuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

glm::vec2 Window::getMousePosition() const
{
    return mousePosition;
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}
