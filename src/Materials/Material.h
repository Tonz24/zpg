//
// Created by Tonz on 26.10.2023.
//

#pragma once


#include "../Shader.h"

class Material {
public:
    virtual void uploadVariables(){
        this->shader.use();
    }

protected:
    explicit Material(const std::string &programName) : shader(*Shader::getShaderProgram(programName)){}
    const Shader& shader;
};


