//
// Created by Tonz on 17.10.2023.
//

#include "SpotLight.h"
#include "../Application.h"


SpotLight::SpotLight(const glm::vec3 &color, Model *model): Light(color, model) {

}

void SpotLight::uploadToGpu() {
    if (!this->active) return;

    this->modelMat = glm::mat4{1};
    this->transform->apply(this->modelMat);

    size_t positionOffset = sizeof(glm::vec4)*3*MAX_N_POINT_LIGHTS + sizeof(glm::vec4)*4*this->uboPosition;

    Application::getInstance().getLightBuffer().setData(positionOffset,sizeof(glm::vec3),&this->color); //color
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec3),sizeof(float),&this->attenuation.x); //constant


    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4),sizeof(glm::vec3),&this->position); //position
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4) + sizeof(glm::vec3),sizeof(float),&this->attenuation.y); //linear

    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*2,sizeof(glm::vec3),&this->direction); //direction
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*2 + sizeof(glm::vec3),sizeof(float),&this->attenuation.z); //quadratic


    float outerCutoffcos = glm::cos(glm::radians(this->outerCutoffAngle));
    float innerCutoffcos = glm::cos(glm::radians(this->innerCutoffAngle));
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*3 ,sizeof(float),&innerCutoffcos); //innerCutoffAngle
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4)*3 + sizeof(float) ,sizeof(float),&outerCutoffcos); //outerCutoffAngle
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

void SpotLight::setOuterCutoffAngle(float cutoffAngle) {
    this->outerCutoffAngle = cutoffAngle;
    this->uploadToGpu();
}

void SpotLight::setInnerCutoffAngle(float cutoffAngle) {
    this->innerCutoffAngle = cutoffAngle;
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

void SpotLight::reassignPositionsImpl(const int &from) {
    SpotLight::reassignPositions(from);
}

void SpotLight::uploadLightCountImpl() {
    SpotLight::uploadLightCount();
}

int SpotLight::assignPositionImpl() {
    return SpotLight::assignPosition();
}

void SpotLight::pushToVector() {
    lights.push_back(this);
}

void SpotLight::releasePositionImpl() {
    SpotLight::releasePosition();
}

void SpotLight::uploadLightSpaceMatrices() const {
    glm::mat4 viewMat = this->getViewMat();
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),sizeof(glm::mat4x4),&viewMat);
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4)*2,sizeof(glm::mat4x4),&this->proj);
}

glm::mat4 SpotLight::getLightSpaceMatrix() const {
    glm::mat4 lSpaceMat = this->proj * this->getViewMat();
    return lSpaceMat;
}

const ConstantMaterial &SpotLight::getMaterial() const {
    return *this->material;
}


