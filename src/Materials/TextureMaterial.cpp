//
// Created by Tonz on 02.10.2023.
//

#include "TextureMaterial.h"

void TextureMaterial::uploadVariables() {
    ConstantMaterial::uploadVariables();
    this->texture.bind(0);
}