//
// Created by Tonz on 16.10.2023.
//

#include "PhongMaterial.h"

void PhongMaterial::uploadVariables() {
    this->shader->setVec3f("objectColor",this->objectColor);
    this->shader->setFloat("specularity",this->specularity);
    this->shader->setFloat("ambientFactor",this->ambientFactor);
    Material::uploadVariables();
}

PhongMaterial::PhongMaterial(const glm::vec3 &objectColor, const float &specularity, const float& ambientFactor) :
    objectColor(objectColor), specularity(specularity), ambientFactor(ambientFactor) {
    this->shader = Shader::getShaderProgram("shader_phong");
}