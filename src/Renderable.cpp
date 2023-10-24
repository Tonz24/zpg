//
// Created by Tonz on 03.10.2023.
//

#include "Renderable.h"
#include "Application.h"

void Renderable::draw() {
    this->material->uploadVariables();
    this->uploadModelMatrix();
    if (model.get() != nullptr)
        this->model->draw();
}

void Renderable::drawForShadowMapping() {
    this->uploadModelMatrix();
    if (model.get() != nullptr)
        this->model->draw();
}

void Renderable::uploadModelMatrix(){
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),glm::value_ptr(this->modelMat));
    glm::mat4x4 normalMatrix = glm::transpose(glm::inverse(this->modelMat));
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4)*3,sizeof(glm::mat4x4),glm::value_ptr(normalMatrix));
}

Renderable::Renderable(Model *model, Material *material): model(std::shared_ptr<Model>(model)), material(std::shared_ptr<Material>(material)){

    this->translation = new Translation();
    this->rotation = new Rotation();
    this->scale = new Scale();

    this->transform = std::make_unique<TransformationComposite>();
    this->transform->addTransformation({this->translation,this->rotation,this->scale});
}

void Renderable::tick() {
    ITickable::tick();
}

void Renderable::setTranslation(const glm::vec3 &translation) {
    this->translation->setTranslation(translation);
    this->applyTransform();
}

void Renderable::translate(const glm::vec3 &translation) {
    this->translation->translate(translation);
    this->applyTransform();
}

void Renderable::setScale(const glm::vec3 &scale) {
    this->scale->setScale(scale);
    this->applyTransform();
}

void Renderable::setRotation(const float& angle,const glm::vec3& axis) {
    this->rotation->setRotation(angle,axis);
    this->applyTransform();
}

void Renderable::rotate(const float &angle) {
    this->rotation->rotate(angle);
    this->applyTransform();
}

void Renderable::applyTransform() {
    this->modelMat = glm::mat4{1};
    this->transform->apply(modelMat);
}

