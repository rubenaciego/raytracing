#pragma once

#include "core/core.hpp"
#include <string>
#include <vector>

class Cubemap
{
private:
    uint32_t texID;

public:
    Cubemap(const std::vector<std::string>& textures);
    Cubemap(const std::string& prefixPath);
    ~Cubemap();

    void bind(uint32_t slot = 0) const;
    uint32_t getID() const;
};
