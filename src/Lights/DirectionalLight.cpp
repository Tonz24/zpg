//
// Created by Tonz on 05.11.2023.
//

#include "DirectionalLight.h"
#include "../Application.h"


DirectionalLight::DirectionalLight(const glm::vec3 &color,const glm::vec3& direction, Model *model): Light(color, model), direction(direction) {

}

void DirectionalLight::uploadToGpu() {
    if (!this->active) return;

    this->modelMat = glm::mat4{1};
    this->transform->apply(this->modelMat);

    size_t positionOffset = sizeof(glm::vec4)*3*MAX_N_POINT_LIGHTS + sizeof(glm::vec4)*4*MAX_N_SPOT_LIGHTS + sizeof(glm::vec4)*3*this->uboPosition;

    Application::getInstance().getLightBuffer().setData(positionOffset,sizeof(glm::vec3),&this->color); //color
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec3),sizeof(float),&this->attenuation.x); //constant

    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4),sizeof(glm::vec3),&this->direction); //direction
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4) + sizeof(glm::vec3),sizeof(float),&this->attenuation.y); //linear

    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4) + sizeof(glm::vec3) + sizeof(float),sizeof(float),&this->attenuation.z); //linear
}

void DirectionalLight::uploadLightCount() {
    Application::getInstance().getLightBuffer().setData(directionalLightOffset,sizeof(int),&lightCount);
}

void DirectionalLight::reassignPositions(const int &from) {
    releasePosition();
    uploadLightCount();
    for (int i = from; i < lights.size(); i++){
        lights.at(i)->uboPosition --;
        lights.at(i)->uploadToGpu();
    }
}

DirectionalLight::~DirectionalLight() {
    reassignPositions(this->uboPosition);
}


void DirectionalLight::setDirection(const glm::vec3 &direction) {
    this->direction = direction;
    this->uploadToGpu();
}

void DirectionalLight::reassignPositionsImpl(const int &from) {
    DirectionalLight::reassignPositions(from);
}

void DirectionalLight::uploadLightCountImpl() {
    DirectionalLight::uploadLightCount();
}

int DirectionalLight::assignPositionImpl() {
    return DirectionalLight::assignPosition();
}

void DirectionalLight::pushToVector() {
    lights.push_back(this);
}

void DirectionalLight::releasePositionImpl() {
    DirectionalLight::releasePosition();
}

void DirectionalLight::uploadLightSpaceMatrices() const {
    glm::mat4 viewMat = this->getViewMat();
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),sizeof(glm::mat4x4),&viewMat);
    //Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4)*2,sizeof(glm::mat4x4),&this->proj);
}

glm::mat4 DirectionalLight::getViewMat() const {
    return glm::mat4();
}

glm::mat4 DirectionalLight::getLightSpaceMatrix() const {
    return glm::mat4();
}

const Material &DirectionalLight::getMaterial() const {
    return *this->material;
}


