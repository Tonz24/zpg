//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"

void Scene::addModel(const std::shared_ptr<IDrawable>& drawable) {
    this->models.push_back(drawable);
}

void Scene::draw() {
    activeCamera->tick();

    for (const auto &tickable : this->tickables){
        tickable->tick();
    }

    for (const auto &model : this->models){
        model->draw();
    }
}


void Scene::addTickable(const std::shared_ptr<ITickable> &tickable) {
    this->tickables.push_back(tickable);
}

void Scene::setCamera(const std::shared_ptr<Camera> &newCamera) {
    this->activeCamera = newCamera;
}
