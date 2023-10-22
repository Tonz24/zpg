//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "LambertMaterial.h"

class PhongMaterial : public LambertMaterial {
public:
    explicit PhongMaterial(const glm::vec3& objectColor = {0.7,0.7,0.7}, const float& diffuseFactor = 1.0f,
                           const float& ambientFactor = 0.1f, const float& specularity = 32.0f, const float& specularFactor = 1.0f);

    virtual void uploadVariables() override;


    void setSpecularity(float specularity);
    void setSpecularFactor(float specularFactor);

protected:
    float specularity{32};
    float specularFactor{1};
};