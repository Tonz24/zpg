//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"
#include <random>


void Scene::addModel(Model &model) {
    this->models.push_back(std::unique_ptr<Model>(&model));
}

void Scene::draw() {
    for (const auto &model : this->models){
        model->getTransform().setRotation(glfwGetTime()*50,AXIS_X);
        model->getTransform().setRotation(glfwGetTime()*50,AXIS_Z);
        model->getTransform().setRotation(glfwGetTime()*50,AXIS_Y);
        model->draw();
    }
}