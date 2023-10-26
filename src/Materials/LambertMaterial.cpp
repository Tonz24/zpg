//
// Created by Tonz on 16.10.2023.
//

#include "LambertMaterial.h"

void LambertMaterial::uploadVariables() {
    ConstantMaterial::uploadVariables();
    this->shader.setFloat("ambientFactor",this->ambientFactor);
    this->shader.setFloat("diffuseFactor", this->diffuseFactor);
}

void LambertMaterial::setAmbientFactor(float ambientFactor) {
    this->ambientFactor = ambientFactor;
}

void LambertMaterial::setDiffuseFactor(float diffuseFactor) {
    this->diffuseFactor = diffuseFactor;
}
