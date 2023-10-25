//
// Created by Tonz on 27.09.2023.
//

#pragma once
#include "../Shader.h"

class ConstantMaterial {
public:
    ConstantMaterial(const glm::vec3& objectColor = {1,1,0}) : objectColor(objectColor), shader(Shader::getShaderProgram("shader_constant")){}

    virtual void uploadVariables();

    [[nodiscard]] const Shader& getShader() const;

    void setObjectColor(const glm::vec3 &objectColor) {
        this->objectColor = objectColor;
    }

protected:
    explicit ConstantMaterial(const std::string& programName, const glm::vec3& objectColor) : shader(Shader::getShaderProgram(programName)), objectColor(objectColor){}

    const Shader* shader;
    glm::vec3 objectColor{1,1,0};
};