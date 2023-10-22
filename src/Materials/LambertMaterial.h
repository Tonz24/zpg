//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "Material.h"

class LambertMaterial : public Material {
public:
    explicit LambertMaterial(const glm::vec3& objectColor = {0.7,0.7,0.7},const float& diffuseFactor = 1.0f, const float& ambientFactor = 1.0f);

    void uploadVariables() override;

    void setObjectColor(const glm::vec3 &objectColor);
    void setAmbientFactor(float ambientFactor);
    void setDiffuseFactor(float diffuseFactor);

protected:
    glm::vec3 objectColor{0.7,0.7,0.7};

    float ambientFactor{0.1};
    float diffuseFactor{1};
};