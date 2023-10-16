//
// Created by Tonz on 16.10.2023.
//

#include "LightMaterial.h"

void LightMaterial::uploadVariables() {
    Material::uploadVariables();
    this->shader->setVec3f("color",this->color);
}

void LightMaterial::setColor(const glm::vec3 &color) {
    this->color = color;
}

LightMaterial::LightMaterial(const glm::vec3 &color) {
    this->shader = Shader::getShaderProgram("shader_light");
}