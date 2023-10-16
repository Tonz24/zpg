//
// Created by Tonz on 16.10.2023.
//

#pragma once


#include "Material.h"

class LightMaterial : public Material {
public:

    LightMaterial(const glm::vec3& color);

    void uploadVariables() override;
    void setColor(const glm::vec3& color);

private:
    glm::vec3 color{1,1,1};
};


