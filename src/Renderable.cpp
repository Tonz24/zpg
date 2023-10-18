//
// Created by Tonz on 03.10.2023.
//

#include "Renderable.h"
#include "Application.h"

void Renderable::draw() {
    this->material->uploadVariables();
    this->uploadModelMatrix();
    this->model->draw();
}

void Renderable::uploadModelMatrix(){

    this->modelMat = glm::mat4{1};
    this->transform->apply(modelMat);

    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),glm::value_ptr(this->modelMat));
}

Renderable::Renderable(Model *model, Material *material, Transformation *transformation)
        : model(std::shared_ptr<Model>(model)), material(std::shared_ptr<Material>(material)){

    TransformationComposite* t = new TransformationComposite();
    this->transform = std::unique_ptr<TransformationComposite>(t);
    Translation * translation = new Translation({0,0,0});
    this->rotation =  new Rotation();
    Scale * scale =  new Scale({1,1,1});

   this->transform = std::shared_ptr<Transformation>(transformation);
}

void Renderable::tick() {
    ITickable::tick();
}
