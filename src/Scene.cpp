//
// Created by Tonz on 26.09.2023.
//
#include "Scene.h"
#include "Application.h"
#include "PostProcessing/PostFX.h"

void Scene::draw() {
    /*Application::getInstance().bindShadowMapShader();
    for (const auto &light : lights){
        light->getShadowFbo().bindDepth();
        glClear(GL_DEPTH_BUFFER_BIT);
        light->uploadLightSpaceMatrices();
        for (const auto &model : this->models){
            model->drawForShadowMapping();
        }
        light->getShadowFbo().unbind();
    }
    PostFX::getInstance().bindPing();
    this->activeCamera->uploadMatrices();*/

    PostFX::getInstance().occlusionMapShader->bind();
    PostFX::getInstance().occlusionMap->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (const auto &model : this->models) {
        model->drawForShadowMapping();
    }
    glDepthFunc(GL_LEQUAL);
    PostFX::getInstance().occlusionMapShader->unbind();
    for (const auto& light : this->rayCasters){
        light->draw();
    }
    glDepthFunc(GL_LESS);

    PostFX::getInstance().bindPing();
    for (const auto &tickable : this->tickables){
        tickable->tick();
    }

    glDepthFunc(GL_LEQUAL);
    for (const auto &model : this->models){
        /*model->getMaterial().getShader().use();
        glm::mat4 lightSpaceMat = lights[0]->getLightSpaceMatrix();
        uint32_t texId = lights[0]->getShadowFbo().getTargetId(0);
        glBindTexture(GL_TEXTURE_2D,texId);
        model->getMaterial().getShader().setVar("lightspaceMat",lightSpaceMat);*/
        model->draw();
    }
    glDepthFunc(GL_LESS);
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

void Scene::addModel(const std::shared_ptr<IDrawable>& drawable) {
    this->models.push_back(drawable);

    if (drawable->canCastRays())
        this->rayCasters.push_back(drawable);
}

void Scene::setActiveCamera(const std::shared_ptr<Camera> &activeCamera) {
    Scene::activeCamera = activeCamera;
}
