//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "Material.h"

class PhongMaterial : public Material {
public:
    explicit PhongMaterial(const glm::vec3& objectColor = {0.7,0.7,0.7}, const float& specularity = 32.0f,
                  const float& ambientFactor = 32.0f, const float& specularFactor = 5.0f);

    void uploadVariables() override;

private:
    glm::vec3 objectColor{0.7,0.7,0.7};
    float specularity{25};
public:
    void setObjectColor(const glm::vec3 &objectColor);

    void setSpecularity(float specularity);

    void setAmbientFactor(float ambientFactor);

    void setSpecularFactor(float specularFactor);

private:
    float ambientFactor{0.1};
    float specularFactor{5};
};