//
// Created by Tonz on 28.09.2023.
//

#pragma once


#include "Material.h"

class LerpMaterial : public Material {
public:
    explicit LerpMaterial(const glm::vec3& color1,const glm::vec3& color2) : color1(color1), color2(color2){
        this->shader = Shader::getShaderProgram("shader_lerp_color");
    }
    LerpMaterial() = delete;
    void uploadVariables() override;
private:
    glm::vec3 color1{0,1,1};
    glm::vec3 color2{1,0,1};
};


