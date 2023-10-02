//
// Created by Tonz on 02.10.2023.
//

#include "TextureMaterial.h"

void TextureMaterial::uploadVariables() {
    Material::uploadVariables();
    this->texture.bind(0);
    this->shader->setFloat("time",Application::getTime());
}