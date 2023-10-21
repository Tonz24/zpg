//
// Created by Tonz on 27.09.2023.
//

#pragma once
#include "Material.h"

class ConstantMaterial : public Material {
public:
    explicit ConstantMaterial(const glm::vec3& color) : color(color){
        this->shader = Shader::getShaderProgram("shader_constant");
    }
    ConstantMaterial() = delete;

    void uploadVariables() override;

private:
    glm::vec3 color{0,1,1};
};


