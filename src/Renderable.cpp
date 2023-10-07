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

void Renderable::initUBO() {
    glGenBuffers(1, &uboId);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBufferData(GL_UNIFORM_BUFFER, 4*4*4, NULL, GL_STATIC_DRAW); //TODO: test whether GL_DYNAMIC_DRAW is faster
    uboInitialized = true;
}

void Renderable::uploadModelMatrix(){
    if (!uboInitialized)
        initUBO();

    this->modelMat = glm::mat4{1};
    if (this->controller != nullptr)
        this->controller->applyPreTransform(modelMat);

    this->transform->apply(modelMat);

    if (this->controller != nullptr)
        this->controller->applyPostTransform(modelMat);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BINDING_POINT, uboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 4*4*4, &this->modelMat);
}

Renderable::Renderable(Model *model, Material *material, TransformationComposite *transformation, Controller* controller)
        : model(std::shared_ptr<Model>(model)), material(std::shared_ptr<Material>(material)){

    TransformationComposite* t = new TransformationComposite();
    this->transform = std::unique_ptr<TransformationComposite>(t);
    Translation * translation = new Translation({0,0,0});
    this->rotation =  new Rotation();
    Scale * scale =  new Scale({1,1,1});

    if (controller != nullptr)
        this->controller = std::shared_ptr<Controller>(controller);

   this->transform = std::shared_ptr<TransformationComposite>(transformation);
}
