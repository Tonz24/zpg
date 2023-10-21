//
// Created by Tonz on 16.10.2023.
//

#include "LambertMaterial.h"

void LambertMaterial::uploadVariables() {
    this->shader->setVec3f("objectColor",this->objectColor);
    this->shader->setFloat("ambientFactor",this->ambientFactor);
    this->shader->setFloat("diffuseFactor", this->diffuseFactor);
    Material::uploadVariables();
}

LambertMaterial::LambertMaterial(const glm::vec3 &objectColor,const float& ambientFactor) : objectColor(objectColor),
    ambientFactor(ambientFactor) {
    this->shader = Shader::getShaderProgram("shader_lambert");
}

void LambertMaterial::setObjectColor(const glm::vec3 &objectColor) {
    this->objectColor = objectColor;
}

void LambertMaterial::setAmbientFactor(float ambientFactor) {
    this->ambientFactor = ambientFactor;
}

void LambertMaterial::setDiffuseFactor(float diffuseFactor) {
    this->diffuseFactor = diffuseFactor;
}
