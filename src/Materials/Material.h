//
// Created by Tonz on 27.09.2023.
//

#pragma once
#include "../Shader.h"

class Material {
public:
    Material() : shader(Shader::getShaderProgram("shader_default")){}

    virtual void uploadVariables();

protected:
    const Shader* shader;
};