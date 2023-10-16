//
// Created by Tonz on 10.10.2023.
//

#include "Light.h"
#include "Application.h"

Light::Light(const glm::vec3& color,TransformationComposite *transformation,  Model *model)
    : Renderable(model,new LightMaterial(color),transformation), color(color){
    this->uboPosition = assignPosition();

    uploadLightCount();
    uploadToGpu();
    this->setColor(this->color);
    lights.push_back(this);
}


Light::~Light() {
    reassignPositions(this->uboPosition);
}

void Light::uploadToGpu() {
    glm::vec4 colorVec = {this->color,0};
    Application::getInstance().getLightBuffer().setData(sizeof(glm::vec4)*3*this->uboPosition,sizeof(glm::vec4),&colorVec); //color

    this->modelMat = glm::mat4{1};
    this->transform->apply(this->modelMat);
    glm::vec4 worldSpacePos = this->modelMat * glm::vec4{0,0,0,1};

    Application::getInstance().getLightBuffer().setData(sizeof(glm::vec4)*3*this->uboPosition + sizeof(glm::vec4),sizeof(glm::vec4),&worldSpacePos); //position

    Application::getInstance().getLightBuffer().setData(sizeof(glm::vec4)*3*this->uboPosition + sizeof(glm::vec3),sizeof(float),&this->attenuation.x); //constant
    Application::getInstance().getLightBuffer().setData(sizeof(glm::vec4)*3*this->uboPosition + sizeof(glm::vec4) + sizeof(glm::vec3),sizeof(float),&this->attenuation.y); //linear
    Application::getInstance().getLightBuffer().setData(sizeof(glm::vec4)*3*this->uboPosition + sizeof(glm::vec4) *2,sizeof(float),&this->attenuation.z); //linear
}

void Light::uploadLightCount() {
    Application::getInstance().getLightBuffer().setData(sizeof(glm::vec4)*3*100 + sizeof(glm::vec3),sizeof(int),&lightCount);
}

void Light::reassignPositions(const int &from) {
    releasePosition();
    uploadLightCount();
    for (int i = from; i < lights.size(); i++){
        lights.at(i)->uboPosition --;
        lights.at(i)->uploadToGpu();
    }
}

void Light::setColor(const glm::vec3 &color) {
    this->color = color;
    dynamic_cast<LightMaterial*>(this->material.get())->setColor(this->color);
    this->uploadToGpu();
}

void Light::setAttenuation(const glm::vec3 &attenuation) {
    this->attenuation = attenuation;
    this->uploadToGpu();
}
