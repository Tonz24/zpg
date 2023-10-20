//
// Created by Tonz on 27.09.2023.
//

#pragma once
#include "Material.h"

class ColorMaterial : public Material {
public:
    explicit ColorMaterial(const glm::vec3& color) : color(color){
        this->shader = Shader::getShaderProgram("shader_color");
    }
    ColorMaterial() = delete;

    void uploadVariables() override;

private:
    glm::vec3 color{0,1,1};
};


