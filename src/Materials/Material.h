//
// Created by Tonz on 26.10.2023.
//

#pragma once


#include "../ShaderProgram.h"

class Material {
public:
    virtual void uploadVariables(){
        this->shader.bind();
    }

    const ShaderProgram &getShader() const {
        return shader;
    }

    virtual void setObjectColor(const glm::vec3 &objectColor) = 0;
protected:
    explicit Material(const std::string &programName) : shader(*ShaderProgram::getShaderProgram(programName)){}
    const ShaderProgram& shader;
};


