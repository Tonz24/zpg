//
// Created by Tonz on 10.10.2023.
//

#include "Light.h"
#include "Application.h"

Light::Light(const glm::vec3& color,TransformationComposite *transformation,  Model *model)
    : Renderable(model,new LightMaterial(color),transformation), color(color) {

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
