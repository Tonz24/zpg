//
// Created by Tonz on 16.10.2023.
//

#include "PhongMaterial.h"

void PhongMaterial::uploadVariables() {
    LambertMaterial::uploadVariables();
    this->shader->setFloat("specularity",this->specularity);
    this->shader->setFloat("specularFactor", this->specularFactor);
}

PhongMaterial::PhongMaterial(const glm::vec3& objectColor, const float& diffuseFactor,const float& ambientFactor, const float& specularity, const float& specularFactor) :
        LambertMaterial(objectColor,diffuseFactor,ambientFactor),specularity(specularity), specularFactor(specularFactor) {
    this->shader = Shader::getShaderProgram("shader_phong");
}

void PhongMaterial::setSpecularity(float specularity) {
    this->specularity = specularity;
}

void PhongMaterial::setSpecularFactor(float specularFactor) {
    this->specularFactor = specularFactor;
}