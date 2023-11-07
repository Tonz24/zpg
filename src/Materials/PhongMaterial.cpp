//
// Created by Tonz on 16.10.2023.
//

#include "PhongMaterial.h"

void PhongMaterial::uploadVariables() {
    LambertMaterial::uploadVariables();
    this->shader.setVar("specularity", this->specularity);
    this->shader.setVar("specularFactor", this->specularFactor);
    int hasSpecular = static_cast<int>(!(this->specularMap == nullptr));
    this->shader.setVar("hasSpecular", hasSpecular);
    if (hasSpecular)
        this->specularMap->bind(1);
}

void PhongMaterial::setSpecularity(float specularity) {
    this->specularity = specularity;
}

void PhongMaterial::setSpecularFactor(float specularFactor) {
    this->specularFactor = specularFactor;
}

void PhongMaterial::setSpecularMap(std::shared_ptr<Texture> specularMap) {
    this->specularMap = std::move(specularMap);
}