#pragma once

#include "core/core.hpp"
#include <string>
#include <unordered_map>

enum class ShaderDataType
{
    INT, BOOL, FLOAT, TEXTURE,
    VEC2, VEC3, VEC4,
    MAT2, MAT3, MAT4
};

enum class ShaderType
{
    VERTEX, FRAGMENT, GEOMETRY,
    LIBRARY 
};

struct ShaderData
{
    ShaderDataType type;
    void* data;
};

class Shader
{
public:
    Shader(const std::string& path);
    ~Shader();
    
    void bind() const;
    uint32_t getID() const;
    
    void setUniformInt(const std::string& name, int value);
    void setUniformBool(const std::string& name, bool value);
    void setUniformFloat(const std::string& name, float value);
    void setUniformVec2(const std::string& name, const glm::vec2& value);
    void setUniformVec2(const std::string& name, float x, float y);
    void setUniformVec3(const std::string& name, const glm::vec3& value);
    void setUniformVec3(const std::string& name, float x, float y, float z);
    void setUniformVec4(const std::string& name, const glm::vec4& value);
    void setUniformVec4(const std::string& name, float x, float y, float z, float w);
    void setUniformMat2(const std::string& name, const glm::mat2& mat);
    void setUniformMat3(const std::string& name, const glm::mat3& mat);
    void setUniformMat4(const std::string& name, const glm::mat4& mat);
    void setUniform(const std::string& name, ShaderData data);

private:
    uint32_t shaderID;
    std::unordered_map<std::string, int> uniformLocations;

    std::unordered_map<ShaderType, std::string> preprocess(std::string& source);
    void checkCompileErrors(GLuint shader, std::string type);
    int getUniformLocation(const std::string& name);
    void readFile(const std::string& path, std::string& res);
};
