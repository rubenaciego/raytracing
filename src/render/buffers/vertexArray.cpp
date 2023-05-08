#include "vertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &bufferID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &bufferID);
}

void VertexArray::bind() const
{
    glBindVertexArray(bufferID);
}

uint32_t VertexArray::getID() const
{
    return bufferID;
}
