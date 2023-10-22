//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"

void Scene::addModel(const std::shared_ptr<IDrawable>& drawable) {
    this->models.push_back(drawable);
}

void Scene::draw() {


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

void Scene::deactivateLights() {
    for (auto &light : this->lights){
        light->deactivate();
    }
}

void Scene::activateLights() {
    for (auto &light : this->lights){
        light->activate();
    }
}

void Scene::addModel(const std::shared_ptr<Light> &light) {
    this->lights.push_back(light);
    std::shared_ptr<IDrawable> lightAsDrawable = light;
    this->addModel(lightAsDrawable);
}
