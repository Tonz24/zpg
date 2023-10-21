//
// Created by Tonz on 27.09.2023.
//

#include "ConstantMaterial.h"

void ConstantMaterial::uploadVariables() {
    Material::uploadVariables();
    shader->setVec3f("color",this->color);
}