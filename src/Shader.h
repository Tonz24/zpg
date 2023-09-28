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
class Shader{
public:
    // the program ID
    uint32_t ID{};

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader() = default;

    // use/activate the shader
    virtual void use() const;

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2f(const std::string& name, glm::vec2 vec) const;
    void setVec2i(const std::string &name, glm::vec<2, int> vec) const;
    void setVec3f(const std::string& name, glm::vec3 vec) const;
    void setVec4f(const std::string& name, glm::vec4 vec) const;
    void setMat4f(const std::string& name, glm::mat4x4 mat) const;

    static void compileShaders();
    static const Shader* getShaderProgram(const std::string& name);

private:

    inline static std::unordered_map<std::string,std::unique_ptr<Shader>> shaderCache{};

    void checkCompileErrors(unsigned int shader, std::string type);
};

