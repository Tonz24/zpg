//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "ConstantMaterial.h"
#include "../Texture.h"

class LambertMaterial : public ConstantMaterial {
public:
    LambertMaterial(const glm::vec3 &objectColor = {1,1,0},const float& diffuseFactor = 1,const float& ambientFactor = 0.1)
    : ConstantMaterial("shader_lambert",objectColor),ambientFactor(ambientFactor), diffuseFactor(diffuseFactor){}

    void uploadVariables() override;

    void setAmbientFactor(float ambientFactor);
    void setDiffuseFactor(float diffuseFactor);

    void setDiffuseMap(std::shared_ptr<Texture> diffuseMap);

protected:
    LambertMaterial(const std::string& programName, const glm::vec3 &objectColor = {1,1,0},const float& diffuseFactor = 1,const float& ambientFactor = 0.1)
            : ConstantMaterial(programName,objectColor),ambientFactor(ambientFactor), diffuseFactor(diffuseFactor){}

    float ambientFactor{0.1};
    float diffuseFactor{1};

    std::shared_ptr<Texture> diffuseMap;
};