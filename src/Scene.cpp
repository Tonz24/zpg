//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"

void Scene::addModel(Renderable &renderable) {
    this->models.push_back(std::unique_ptr<Renderable>(&renderable));
}

void Scene::draw() {
    cam.uploadMatrices();
    for (const auto &renderable : this->models){
        renderable->draw();
    }
}