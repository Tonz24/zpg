//
// Created by Tonz on 27.09.2023.
//

#include "ConstantMaterial.h"
#include "../Application.h"

void ConstantMaterial::uploadVariables() {
    Material::uploadVariables();
    this->shader.setFloat("time",Application::getInstance().getTime());
    this->shader.setVec3f("objectColor",this->objectColor);
}

const Shader &ConstantMaterial::getShader() const {
    return this->shader;
}