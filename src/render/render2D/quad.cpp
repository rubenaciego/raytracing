#include "quad.hpp"

uint32_t indices[] = {
    0, 1, 2,
    2, 3, 0
};

Quad::Quad(Vertex2D vertices[4])
{
    vao.bind();

    vbo.setData(vertices, 4 * sizeof(Vertex2D));
    vbo.setAttribute(0, 2, GL_FLOAT, false, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
    vbo.setAttribute(1, 2, GL_FLOAT, false, sizeof(Vertex2D), (void*)offsetof(Vertex2D, texCoord));

    ibo.setData(indices, 6);
}

Quad::Quad(const glm::vec2& position, const glm::vec2& size)
{
    Vertex2D vertices[4];

    vertices[0].position = position;
    vertices[0].texCoord = { 0.0f, 0.0f };
    vertices[1].position = position + glm::vec2(size.x, 0.0f);
    vertices[1].texCoord = { 1.0f, 0.0f };
    vertices[2].position = position + size;
    vertices[2].texCoord = { 1.0f, 1.0f };
    vertices[3].position = position + glm::vec2(0.0f, size.y);
    vertices[3].texCoord = { 0.0f, 1.0f };

    vao.bind();

    vbo.setData(vertices, 4 * sizeof(Vertex2D));
    vbo.setAttribute(0, 2, GL_FLOAT, false, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
    vbo.setAttribute(1, 2, GL_FLOAT, false, sizeof(Vertex2D), (void*)offsetof(Vertex2D, texCoord));

    ibo.setData(indices, 6);
}

void Quad::bind() const
{
    vao.bind();
}
