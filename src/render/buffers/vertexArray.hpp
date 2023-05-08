#pragma once

#include "core/core.hpp"

class VertexArray
{
private:
    uint32_t bufferID;

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    uint32_t getID() const;
};
