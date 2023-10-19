//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "../Shader.h"

class ImageEffect {
public:

    explicit ImageEffect(const glm::vec3& filter);
    void apply();

private:
    glm::vec3 filter{0,0,1};
    const Shader& shader;
};


