//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"
#include "Application.h"
#include "PostProcessing/PostFX.h"

void Scene::addModel(const std::shared_ptr<IDrawable>& drawable) {
    this->models.push_back(drawable);
}

void Scene::draw() {
    glEnable(GL_DEPTH_TEST);
    Application::getInstance().bindShadowMapShader();
    for (const auto &light : lights){
        //TODO: bind light's fbo
        light->getShadowFbo().bindDepth();
        glClear(GL_DEPTH_BUFFER_BIT);
        light->uploadLightSpaceMatrices();
        for (const auto &model : this->models){
            model->drawForShadowMapping();
        }
    }
    PostFX::getInstance().bindPing();
    this->activeCamera->uploadMatrices();

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

void Scene::setActiveCamera(const std::shared_ptr<Camera> &activeCamera) {
    Scene::activeCamera = activeCamera;
}
