//
// Created by Tonz on 16.10.2023.
//

#include "PhongMaterial.h"

void PhongMaterial::uploadVariables() {
    this->shader->setVec3f("objectColor",this->objectColor);
    this->shader->setFloat("specularity",this->specularity);
    this->shader->setFloat("ambientFactor",this->ambientFactor);
    this->shader->setFloat("specularFactor", this->specularFactor);
    Material::uploadVariables();
}

PhongMaterial::PhongMaterial(const glm::vec3 &objectColor, const float &specularity, const float& ambientFactor, const float& specularFactor) :
    objectColor(objectColor), specularity(specularity), ambientFactor(ambientFactor), specularFactor(specularFactor) {
    this->shader = Shader::getShaderProgram("shader_phong");
}

void PhongMaterial::setObjectColor(const glm::vec3 &objectColor) {
    this->objectColor = objectColor;
}

void PhongMaterial::setSpecularity(float specularity) {
    this->specularity = specularity;
}

void PhongMaterial::setAmbientFactor(float ambientFactor) {
    this->ambientFactor = ambientFactor;
}

void PhongMaterial::setSpecularFactor(float specularFactor) {
    this->specularFactor = specularFactor;
}
