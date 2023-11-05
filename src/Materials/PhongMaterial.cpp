//
// Created by Tonz on 16.10.2023.
//

#include "PhongMaterial.h"

void PhongMaterial::uploadVariables() {
    LambertMaterial::uploadVariables();
    this->shader.setVar("specularity", this->specularity);
    this->shader.setVar("specularFactor", this->specularFactor);
}

void PhongMaterial::setSpecularity(float specularity) {
    this->specularity = specularity;
}

void PhongMaterial::setSpecularFactor(float specularFactor) {
    this->specularFactor = specularFactor;
}