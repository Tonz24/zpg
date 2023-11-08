//
// Created by Tonz on 10.10.2023.
//

#include "Light.h"
#include "../Application.h"

Light::Light(const glm::vec3& color, Model *model)
    : SceneObject(model, new ConstantMaterial(color)), color(color) {
    this->shadowFBO = std::make_unique<Framebuffer>(5.0f);
    this->castRays = true;
}
void Light::setColor(const glm::vec3 &color) {
    this->color = color;
    this->material->setObjectColor(color);
    this->uploadToGpu();
}

void Light::setAttenuation(const glm::vec3 &attenuation) {
    this->attenuation = attenuation;
    this->uploadToGpu();
}

void Light::draw() {
    SceneObject::draw();
}

void Light::tick() {
    SceneObject::tick();
}

void Light::setTranslation(const glm::vec3 &translation) {
    SceneObject::setTranslation(translation);
    this->uploadToGpu();
}

void Light::translate(const glm::vec3 &translation) {
    SceneObject::translate(translation);
    this->uploadToGpu();
}

void Light::setRotation(const float &angle, const glm::vec3 &axis) {
    SceneObject::setRotation(angle, axis);
    this->uploadToGpu();
}

void Light::rotate(const float &angle) {
    SceneObject::rotate(angle);
    this->uploadToGpu();
}

void Light::setScale(const glm::vec3 &scale) {
    SceneObject::setScale(scale);
    this->uploadToGpu();
}

void Light::activate() {
    if (!this->active) {
        this->active = true;
        this->uboPosition = this->assignPositionImpl();
        this->uploadLightCountImpl();
        this->uploadToGpu();
    }
}

void Light::deactivate() {
    if (this->active) {
        this->active = false;
        this->reassignPositionsImpl(this->uboPosition);
    }
}

const Framebuffer& Light::getShadowFbo() const {
    return *shadowFBO;
}
