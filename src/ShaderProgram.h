#pragma once
#include "GL/glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//https://learnopengl.com/Getting-started/Shaders
class ShaderProgram{
public:

    void bind() const;
    void unbind() const;

    void setVar(const std::string& name, bool value) const;
    void setVar(const std::string& name, int value) const;
    void setVar(const std::string& name, float value) const;
    void setVar(const std::string& name, const glm::vec2& vec) const;
    void setVar(const std::string& name, const glm::vec<2, int>& vec) const;
    void setVar(const std::string& name, const glm::vec3& vec) const;
    void setVar(const std::string& name, const glm::vec4& vec) const;
    void setVar(const std::string& name, const glm::mat4x4& mat) const;

    static void compileShaders();
    static const ShaderProgram* getShaderProgram(const std::string& name);

private:
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    ShaderProgram(const char* vertexPath,const char* geometryPath, const char* fragmentPath);
    uint32_t id{0};

    inline static std::unordered_map<std::string,std::unique_ptr<ShaderProgram>> shaderCache{};
    static void checkCompileErrors(unsigned int shader, const std::string& type);

    static std::string loadShader(const std::string& path);
};