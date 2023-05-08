#pragma once

#include "core/core.hpp"
#include "render/shader.hpp"
#include <unordered_map>

class Material
{
public:
    virtual ~Material() = default;

    Shader* shader;

    virtual void updateShaderData(Shader* shader) const = 0;
};

class GenericMaterial : public Material
{
private:
    std::unordered_map<std::string, ShaderData> materialData;

public:
    virtual void updateShaderData(Shader* shader) const override;
    void add(const std::string& name, ShaderData data);
    void erase(const std::string& name);
};
