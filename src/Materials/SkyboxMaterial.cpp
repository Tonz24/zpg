//
// Created by Tonz on 07.11.2023.
//

#include "SkyboxMaterial.h"

SkyboxMaterial::SkyboxMaterial(const std::string &path) : Material("shader_skybox") {
    this->skybox = std::make_shared<Texture>(path, SkyboxMaterial::faces);
}

void SkyboxMaterial::uploadVariables() {
    Material::uploadVariables();
    this->skybox->bindCubemap(0);
}

void SkyboxMaterial::setObjectColor(const glm::vec3 &objectColor) {
}
