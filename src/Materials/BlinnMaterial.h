//
// Created by Tonz on 16.10.2023.
//

#pragma once


#include "PhongMaterial.h"

class BlinnMaterial : public PhongMaterial {
public:
    BlinnMaterial(const glm::vec3& objectColor = {1,1,0}, const float& diffuseFactor = 1,const float& ambientFactor = 0.1,
                const float& specularity = 32, const float& specularFactor = 1) :
                PhongMaterial("shader_blinn",objectColor,diffuseFactor,ambientFactor,specularity,specularFactor) {}
};