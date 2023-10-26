//
// Created by Tonz on 02.10.2023.
//

#pragma once
#include "ConstantMaterial.h"
#include "../Texture.h"

class TextureMaterial : public Material {
public:
    explicit TextureMaterial(Texture& texture) : Material("shader_texture"), texture(texture) {}
    TextureMaterial() = delete;

    void uploadVariables() override;

private:
    Texture& texture;
};