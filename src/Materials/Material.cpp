//
// Created by Tonz on 27.09.2023.
//

#include "Material.h"
#include "../Application.h"

void Material::uploadVariables() {
    this->shader->use();
    this->shader->setFloat("time",Application::getInstance().getTime());
}