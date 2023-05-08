#pragma once

#include "core/core.hpp"

class VertexBuffer
{
private:
    uint32_t bufferID;

public:
    VertexBuffer();
    VertexBuffer(const void* data, size_t size);
    ~VertexBuffer();

    void bind() const;
    void setData(const void* data, size_t size) const;
    void setAttribute(uint32_t index, int count, GLenum type, bool normalized, size_t stride, void* offset) const;
    uint32_t getID() const;
};
