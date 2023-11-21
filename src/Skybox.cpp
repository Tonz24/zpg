//
// Created by Tonz on 12.11.2023.
//

#include "Skybox.h"
#include "Materials/SkyboxMaterial.h"
#include "Models/Cube.h"

void Skybox::draw() {
    this->material->uploadVariables();
    this->model->draw();
}

void Skybox::drawForShadowMapping() {

}

const Material &Skybox::getMaterial() const {
    return *this->material;
}

const bool &Skybox::canCastRays() const {
    return dummmy;
}

void Skybox::setCanCastRays(bool value) {

}

const glm::mat4 &Skybox::getModelMat() const {
    return dummy;
}

Skybox::Skybox(const std::string &path) : material(std::make_shared<SkyboxMaterial>(path)), model(std::make_shared<Cube>()), IDrawable() {}
