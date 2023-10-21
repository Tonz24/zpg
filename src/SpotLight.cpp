//
// Created by Tonz on 17.10.2023.
//

#include "SpotLight.h"
#include "Application.h"


SpotLight::SpotLight(const glm::vec3 &color, Model *model): Light(color, model) {

    this->uboPosition = assignPosition();
    uploadLightCount();

    this->setColor(this->color);
    lights.push_back(this);
}

void SpotLight::uploadToGpu() {

    this->modelMat = glm::mat4{1};
    this->transform->apply(this->modelMat);
    glm::vec4 worldSpacePos = this->modelMat * glm::vec4{0,0,0,1};

    size_t positionOffset = sizeof(glm::vec4)*3*MAX_N_POINT_LIGHTS + sizeof(glm::vec4)*4*this->uboPosition;

    Application::getInstance().getLightBuffer().setData(positionOffset,sizeof(glm::vec3),&this->color); //color
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec3),sizeof(float),&this->attenuation.x); //constant


    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4),sizeof(glm::vec3),&this->position); //position
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4) + sizeof(glm::vec3),sizeof(float),&this->attenuation.y); //linear

    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*2,sizeof(glm::vec3),&this->direction); //direction
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*2 + sizeof(glm::vec3),sizeof(float),&this->attenuation.z); //quadratic


    float cutOffcos = glm::cos(glm::radians(this->cutoffAngle));
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*3 ,sizeof(float),&cutOffcos); //cutoffAngle
}

void SpotLight::uploadLightCount() {
    Application::getInstance().getLightBuffer().setData(spotLightOffset,sizeof(int),&lightCount);
}

void SpotLight::reassignPositions(const int &from) {
    releasePosition();
    uploadLightCount();
    for (int i = from; i < lights.size(); i++){
        lights.at(i)->uboPosition --;
        lights.at(i)->uploadToGpu();
    }
}

SpotLight::~SpotLight() {
    reassignPositions(this->uboPosition);
}

void SpotLight::setCutoffAngle(float cutoffAngle) {
    this->cutoffAngle = cutoffAngle;
    this->uploadToGpu();
}

void SpotLight::setDirection(const glm::vec3 &direction) {
    this->direction = direction;
    this->uploadToGpu();
}

void SpotLight::setPosition(const glm::vec3 &position) {
    SpotLight::position = position;
    this->uploadToGpu();
}