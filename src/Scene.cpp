//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"

void Scene::addModel(Renderable &renderable) {
    this->models.push_back(std::unique_ptr<Renderable>(&renderable));
}

void Scene::draw() {
    this->camera->uploadMatrices();
    for (const auto &renderable : this->models){
        renderable->draw();
    }
}

void Scene::setCamera(Camera* camera) {
    std::unique_ptr<Camera> newCam = std::unique_ptr<Camera>(camera);
    std::swap(this->camera,newCam);
}
