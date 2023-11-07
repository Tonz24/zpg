//
// Created by Tonz on 16.10.2023.
//

#include "LambertMaterial.h"

void LambertMaterial::uploadVariables() {
    ConstantMaterial::uploadVariables();
    this->shader.setVar("ambientFactor", this->ambientFactor);
    this->shader.setVar("diffuseFactor", this->diffuseFactor);
    int hasDiffuse = static_cast<int>(!(this->diffuseMap == nullptr));
    this->shader.setVar("hasDiffuse", hasDiffuse);

    if (hasDiffuse){
        this->diffuseMap->bind(0);
    }
}

void LambertMaterial::setAmbientFactor(float ambientFactor) {
    this->ambientFactor = ambientFactor;
}

void LambertMaterial::setDiffuseFactor(float diffuseFactor) {
    this->diffuseFactor = diffuseFactor;
}

void LambertMaterial::setDiffuseMap(std::shared_ptr<Texture> diffuseMap) {
    LambertMaterial::diffuseMap = std::move(diffuseMap);
}