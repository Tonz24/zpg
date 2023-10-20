//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "Material.h"

class PhongMaterial : public Material {
public:
    explicit PhongMaterial(const glm::vec3& objectColor = {0.7,0.7,0.7}, const float& specularity = 32.0f,
                  const float& ambientFactor = 32.0f, const float& specularFactor = 5.0f);

    virtual void uploadVariables() override;

    void setObjectColor(const glm::vec3 &objectColor);
    void setSpecularity(float specularity);
    void setAmbientFactor(float ambientFactor);
    void setSpecularFactor(float specularFactor);
    void setDiffuseFactor(float diffuseFactor);

protected:
    glm::vec3 objectColor{0.7,0.7,0.7};
    float specularity{25};

    float ambientFactor{0.1};
    float specularFactor{5};
    float diffuseFactor{1};
};