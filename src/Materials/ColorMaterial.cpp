//
// Created by Tonz on 27.09.2023.
//

#include "ColorMaterial.h"

void ColorMaterial::uploadVariables() {
    Material::uploadVariables();
    shader->setVec3f("color",this->color);
}