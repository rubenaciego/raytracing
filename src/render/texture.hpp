#pragma once

#include "core/core.hpp"
#include <string>

class Texture
{
private:
    uint32_t texID;

public:
    Texture(const std::string& path);
    Texture(void* data, int width, int height, GLenum format);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void setData(void* data, int width, int height, GLenum format);
    uint32_t getID() const;
};
