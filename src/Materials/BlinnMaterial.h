//
// Created by Tonz on 16.10.2023.
//

#pragma once


#include "PhongMaterial.h"

class BlinnMaterial : public PhongMaterial {
public:
    explicit BlinnMaterial(const glm::vec3& objectColor = {0.7,0.7,0.7}, const float& specularity = 32.0f,
                           const float& ambientFactor = 32.0f, const float& specularFactor = 5.0f);
};


