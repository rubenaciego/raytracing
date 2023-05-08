#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &bufferID);
}

IndexBuffer::IndexBuffer(const uint32_t* indices, size_t count) : IndexBuffer()
{
    setData(indices, count);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &bufferID);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::setData(const uint32_t* indices, size_t count) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

uint32_t IndexBuffer::getID() const
{
    return bufferID;
}
