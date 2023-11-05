//
// Created by Tonz on 27.09.2023.
//

#include "ConstantMaterial.h"
#include "../Application.h"

void ConstantMaterial::uploadVariables() {
    Material::uploadVariables();
    this->shader.setVar("time", Application::getInstance().getTime());
    this->shader.setVar("objectColor", this->objectColor);
}

const ShaderProgram &ConstantMaterial::getShader() const {
    return this->shader;
}