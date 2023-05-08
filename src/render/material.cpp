#include "material.hpp"
#include "render/texture.hpp"
#include <iostream>

void GenericMaterial::updateShaderData(Shader* shader) const
{
    int samplerSlot = 0;

    for (std::unordered_map<std::string, ShaderData>::const_iterator i = materialData.begin();
        i != materialData.end(); ++i)
    {
        if (i->second.type == ShaderDataType::TEXTURE)
        {
            Texture* texture = (Texture*)i->second.data;
            texture->bind(samplerSlot);
            shader->setUniformInt(i->first, samplerSlot);
            ++samplerSlot;
        }
        else
            shader->setUniform(i->first, i->second);
    }
}

void GenericMaterial::add(const std::string& name, ShaderData data)
{
    materialData[name] = data;
}

void GenericMaterial::erase(const std::string& name)
{
    materialData.erase(name);
}
