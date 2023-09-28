//
// Created by Tonz on 26.09.2023.
//

#include "Scene.h"

void Scene::addModel(Model &model) {
    this->models.push_back(std::unique_ptr<Model>(&model));
}

void Scene::draw() {
    for (const auto &model : this->models){
        model->draw();
    }
}
