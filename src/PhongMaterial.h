//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "Material.h"

class PhongMaterial : public Material {
public:
    PhongMaterial(const glm::vec3& objectColor = {0.7,0.7,0.7}, const float& specularity = 32.0f);
    void uploadVariables() override;
private:
    glm::vec3 objectColor{0.7,0.7,0.7};
    float specularity{25};
};