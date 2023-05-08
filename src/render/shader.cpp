#include "shader.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

static ShaderType shaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return ShaderType::VERTEX;
	else if (type == "fragment" || type == "pixel")
		return ShaderType::FRAGMENT;
    else if (type == "geometry")
        return ShaderType::GEOMETRY;
    else // if (type == "library")
        return ShaderType::LIBRARY;
}

static GLenum shaderTypeToGL(ShaderType type)
{
    assert(type != ShaderType::LIBRARY);

    switch (type)
    {
        case ShaderType::VERTEX: return GL_VERTEX_SHADER;
        case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
        case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
        default: return -1;
    }
}

size_t shaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::INT: return sizeof(int);
        case ShaderDataType::BOOL: return sizeof(bool);
        case ShaderDataType::FLOAT: return sizeof(float);
        case ShaderDataType::TEXTURE: return sizeof(int);
        case ShaderDataType::VEC2: return sizeof(glm::vec2);
        case ShaderDataType::VEC3: return sizeof(glm::vec3);
        case ShaderDataType::VEC4: return sizeof(glm::vec4);
        case ShaderDataType::MAT2: return sizeof(glm::mat2);
        case ShaderDataType::MAT3: return sizeof(glm::mat3);
        case ShaderDataType::MAT4: return sizeof(glm::mat4);
    };

    return 0;
}

Shader::Shader(const std::string& path)
{
    std::string shaderCode;
    readFile(path, shaderCode);

    std::unordered_map<ShaderType, std::string> sources = preprocess(shaderCode);
    std::vector<uint32_t> shaders(sources.size());
    shaderID = glCreateProgram();
    size_t i = 0;

    for (std::unordered_map<ShaderType, std::string>::const_iterator it = sources.begin(); it != sources.end(); ++it)
    {
        auto type = shaderTypeToGL(it->first);
        const char* code = it->second.c_str();
        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &code, nullptr);
        glCompileShader(shader);

        if (type == GL_VERTEX_SHADER)
            checkCompileErrors(shader, "VERTEX");
        else if (type == GL_FRAGMENT_SHADER)
            checkCompileErrors(shader, "FRAGMENT");
        else if (type == GL_GEOMETRY_SHADER)
            checkCompileErrors(shader, "GEOMETRY");

        glAttachShader(shaderID, shader);
        shaders[i++] = shader;
    }
    
    glLinkProgram(shaderID);

    for (i = 0; i < shaders.size(); ++i)
        glDeleteShader(shaders[i]);

    checkCompileErrors(shaderID, "PROGRAM");
}

Shader::~Shader()
{
    glDeleteProgram(shaderID);
}

std::unordered_map<ShaderType, std::string> Shader::preprocess(std::string& source)
{   
    /* Process includes */
    const char* includeToken = "#include";
    size_t includeTokenLength = strlen(includeToken);
    size_t pos = source.find(includeToken, 0);

    while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		assert(eol != std::string::npos);
		size_t begin = pos + includeTokenLength + 1;

        /* Should be like #include "source.glsl" */
		std::string file = source.substr(begin + 1, eol - begin - 2);
        std::string fileSource;
        readFile(file, fileSource);
        std::string code = preprocess(fileSource)[ShaderType::LIBRARY];

        source.erase(pos, eol - pos);
        source.insert(pos, code);

		pos = source.find(includeToken, 0);
	}

    /* Split shaders in different types */
    std::unordered_map<ShaderType, std::string> shaderSources;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	pos = source.find(typeToken, 0);

	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		assert(eol != std::string::npos);
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		assert(nextLinePos != std::string::npos);
		pos = source.find(typeToken, nextLinePos);

		shaderSources[shaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
	}

    if (shaderSources.size() == 0)
        shaderSources[ShaderType::LIBRARY] = source;
    
    return shaderSources;
}

void Shader::bind() const 
{ 
    glUseProgram(shaderID); 
}

uint32_t Shader::getID() const
{
    return shaderID;
}

void Shader::setUniformInt(const std::string& name, int value)
{
    int loc = getUniformLocation(name);
    glUniform1i(loc, value);
}

void Shader::setUniformBool(const std::string& name, bool value)
{
    int loc = getUniformLocation(name);
    glUniform1i(loc, value);
}

void Shader::setUniformFloat(const std::string& name, float value)
{
    int loc = getUniformLocation(name);
    glUniform1f(loc, value);
}

void Shader::setUniformVec2(const std::string& name, const glm::vec2& value)
{
    int loc = getUniformLocation(name);
    glUniform2f(loc, value.x, value.y);
}

void Shader::setUniformVec2(const std::string& name, float x, float y)
{
    int loc = getUniformLocation(name);
    glUniform2f(loc, x, y);   
}

void Shader::setUniformVec3(const std::string& name, const glm::vec3& value)
{
    int loc = getUniformLocation(name);
    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setUniformVec3(const std::string& name, float x, float y, float z)
{
    int loc = getUniformLocation(name);
    glUniform3f(loc, x, y, z);
}

void Shader::setUniformVec4(const std::string& name, const glm::vec4& value)
{
    int loc = getUniformLocation(name);
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Shader::setUniformVec4(const std::string& name, float x, float y, float z, float w)
{
    int loc = getUniformLocation(name);
    glUniform4f(loc, x, y, z, w);
}

void Shader::setUniformMat2(const std::string& name, const glm::mat2& mat)
{
    int loc = getUniformLocation(name);
    glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniformMat3(const std::string& name, const glm::mat3& mat)
{
    int loc = getUniformLocation(name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat)
{
    int loc = getUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform(const std::string& name, ShaderData data)
{
    switch (data.type)
    {
        case ShaderDataType::INT: setUniformInt(name, *(int*)data.data); break;
        case ShaderDataType::BOOL: setUniformBool(name, *(bool*)data.data); break;
        case ShaderDataType::FLOAT: setUniformFloat(name, *(float*)data.data); break;
        case ShaderDataType::TEXTURE: setUniformInt(name, *(int*)data.data); break;
        case ShaderDataType::VEC2: setUniformVec2(name, *(glm::vec2*)data.data); break;
        case ShaderDataType::VEC3: setUniformVec3(name, *(glm::vec3*)data.data); break;
        case ShaderDataType::VEC4: setUniformVec4(name, *(glm::vec4*)data.data); break;
        case ShaderDataType::MAT2: setUniformMat2(name, *(glm::mat2*)data.data); break;
        case ShaderDataType::MAT3: setUniformMat3(name, *(glm::mat3*)data.data); break;
        case ShaderDataType::MAT4: setUniformMat4(name, *(glm::mat4*)data.data); break;
    };
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl << infoLog << std::endl;
        }
    }
}

int Shader::getUniformLocation(const std::string& name)
{
    int loc;
    auto it = uniformLocations.find(name);

    if (it == uniformLocations.end())
    {
        loc = glGetUniformLocation(shaderID, name.c_str());
        uniformLocations[name] = loc;

        if (loc == -1)
            std::cout << "ERROR: UNIFORM " << name << " DOES NOT EXIST" << std::endl;
    }
    else
        loc = it->second;

    return loc;
}

void Shader::readFile(const std::string& path, std::string& res)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(path);
        std::stringstream shaderStream, fShaderStream;
        
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        
        res = shaderStream.str();		

    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << path << std::endl;
    }
}
