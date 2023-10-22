//
// Created by Tonz on 10.10.2023.
//

#include "Light.h"
#include "Application.h"

Light::Light(const glm::vec3& color, Model *model)
    : Renderable(model,new LightMaterial(color)), color(color) {

}
void Light::setColor(const glm::vec3 &color) {
    this->color = color;
    dynamic_cast<LightMaterial*>(this->material.get())->setColor(this->color);
    this->uploadToGpu();
}

void Light::setAttenuation(const glm::vec3 &attenuation) {
    this->attenuation = attenuation;
    this->uploadToGpu();
}

void Light::draw() {
    Renderable::draw();
}

void Light::tick() {
    Renderable::tick();
}

void Light::setTranslation(const glm::vec3 &translation) {
    Renderable::setTranslation(translation);
    this->uploadToGpu();
}

void Light::translate(const glm::vec3 &translation) {
    Renderable::translate(translation);
    this->uploadToGpu();
}

void Light::setRotation(const float &angle, const glm::vec3 &axis) {
    Renderable::setRotation(angle, axis);
    this->uploadToGpu();
}

void Light::rotate(const float &angle) {
    Renderable::rotate(angle);
    this->uploadToGpu();
}

void Light::setScale(const glm::vec3 &scale) {
    Renderable::setScale(scale);
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