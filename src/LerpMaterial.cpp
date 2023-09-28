//
// Created by Tonz on 28.09.2023.
//

#include "LerpMaterial.h"

void LerpMaterial::uploadVariables() {
    Material::uploadVariables();
    shader->setVec3f("color1",this->color1);
    shader->setVec3f("color2",this->color2);
}
