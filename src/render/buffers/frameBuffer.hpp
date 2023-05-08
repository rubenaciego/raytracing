#pragma once

#include "core/core.hpp"

class FrameBuffer
{
private:
    uint32_t bufferID;
    uint32_t color;
    uint32_t depthStencil;

    uint32_t width;
    uint32_t height;

    bool renderBuffer;

public:
    FrameBuffer(uint32_t width, uint32_t height, bool useRenderBuffer);
    ~FrameBuffer();

    void bind() const;
    uint32_t getID() const;
    uint32_t getColorID() const;
    uint32_t getDepthStencilID() const;
    uint32_t getWidth() const;
    uint32_t getHeight() const;
};
