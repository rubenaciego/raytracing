#pragma once

#include "core/core.hpp"
#include "render/buffers/indexBuffer.hpp"
#include "render/buffers/vertexBuffer.hpp"
#include "render/buffers/vertexArray.hpp"

struct Vertex2D
{
    glm::vec2 position;
    glm::vec2 texCoord;
};

class Quad
{
private:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;

public:
    Quad(Vertex2D vertices[4]);
    Quad(const glm::vec2& position, const glm::vec2& size);

    void bind() const;
};
