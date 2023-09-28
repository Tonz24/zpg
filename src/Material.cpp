//
// Created by Tonz on 27.09.2023.
//

#include "Material.h"

void Material::uploadVariables() {
    this->shader->use();
}

void Material::uploadTranslation(const glm::vec3& translation) {
    this->shader->use();
    this->shader->setVec3f("translation",translation);
}
