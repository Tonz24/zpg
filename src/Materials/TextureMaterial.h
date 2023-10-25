//
// Created by Tonz on 02.10.2023.
//

#pragma once
#include "ConstantMaterial.h"
#include "../Texture.h"

class TextureMaterial : public ConstantMaterial {
public:
    explicit TextureMaterial(Texture& texture) : texture(texture){
        this->shader = Shader::getShaderProgram("shader_texture");
    }
    TextureMaterial() = delete;

    void uploadVariables() override;

private:
    Texture& texture;
};