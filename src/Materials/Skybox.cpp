//
// Created by Tonz on 07.11.2023.
//

#include "Skybox.h"

Skybox::Skybox(const std::string &path) : Material("shader_skybox") {
    this->skybox = std::make_shared<Texture>(path,Skybox::faces);
}

void Skybox::uploadVariables() {
    Material::uploadVariables();
    this->skybox->bindCubemap(0);
}

void Skybox::setObjectColor(const glm::vec3 &objectColor) {
}
