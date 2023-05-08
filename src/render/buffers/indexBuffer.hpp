#pragma once

#include "core/core.hpp"

class IndexBuffer
{
private:
    uint32_t bufferID;

public:
    IndexBuffer();
    IndexBuffer(const uint32_t* indices, size_t count);
    ~IndexBuffer();

    void bind() const;
    void setData(const uint32_t* indices, size_t count) const;
    uint32_t getID() const;
};
