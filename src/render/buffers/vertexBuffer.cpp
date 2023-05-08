#include "vertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &bufferID);
}

VertexBuffer::VertexBuffer(const void* data, size_t size) : VertexBuffer()
{
    setData(data, size);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &bufferID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::setData(const void* data, size_t size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::setAttribute(uint32_t index, int count, GLenum type, bool normalized, size_t stride, void* offset) const
{
    glVertexAttribPointer(index, count, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}

uint32_t VertexBuffer::getID() const
{
    return bufferID;
}
