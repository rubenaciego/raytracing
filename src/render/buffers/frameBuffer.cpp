#include "frameBuffer.hpp"
#include <iostream>

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, bool useRenderBuffer) :
    width(width), height(height), renderBuffer(useRenderBuffer)
{
    glGenFramebuffers(1, &bufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, bufferID);

    glGenTextures(1, &color);
    glBindTexture(GL_TEXTURE_2D, color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);

    if (useRenderBuffer)
    {
        glGenRenderbuffers(1, &depthStencil);
        glBindRenderbuffer(GL_RENDERBUFFER, depthStencil);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencil);
    }
    else
    {
        glGenTextures(1, &depthStencil);
        glBindTexture(GL_TEXTURE_2D, depthStencil);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencil, 0);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR: FRAMEBUFFER CREATION FAILED" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &bufferID);
    glDeleteTextures(1, &color);

    if (renderBuffer)
        glDeleteRenderbuffers(1, &depthStencil);
    else
        glDeleteTextures(1, &depthStencil);
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
}

uint32_t FrameBuffer::getID() const
{
    return bufferID;
}

uint32_t FrameBuffer::getColorID() const
{
    return color;
}

uint32_t FrameBuffer::getDepthStencilID() const
{
    return depthStencil;
}

uint32_t FrameBuffer::getWidth() const
{
    return width;
}

uint32_t FrameBuffer::getHeight() const
{
    return height;
}
