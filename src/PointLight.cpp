//
// Created by Tonz on 17.10.2023.
//

#include "PointLight.h"
#include "Application.h"

PointLight::PointLight(const glm::vec3 &color, TransformationComposite *transformation, Model *model)
            : Light(color, transformation, model) {

    this->uboPosition = assignPosition();
    this->setColor(this->color);
    uploadLightCount();
    lights.push_back(this);
}

void PointLight::uploadToGpu() {
    glm::vec4 colorVec = {this->color,0};

    size_t positionOffset = sizeof(glm::vec4)*3*this->uboPosition;
    Application::getInstance().getLightBuffer().setData(positionOffset,sizeof(glm::vec4),&colorVec); //color

    this->modelMat = glm::mat4{1};
    this->transform->apply(this->modelMat);
    glm::vec4 worldSpacePos = this->modelMat * glm::vec4{0,0,0,1};

    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4),sizeof(glm::vec4),&worldSpacePos); //position

    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec3),sizeof(float),&this->attenuation.x); //constant
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4) + sizeof(glm::vec3),sizeof(float),&this->attenuation.y); //linear
    Application::getInstance().getLightBuffer().setData(positionOffset + sizeof(glm::vec4) *2,sizeof(float),&this->attenuation.z); //linear
}

void PointLight::uploadLightCount() {
    Application::getInstance().getLightBuffer().setData(pointLightOffset,sizeof(int),&lightCount);
}

void PointLight::reassignPositions(const int &from) {
    releasePosition();
    uploadLightCount();
    for (int i = from; i < lights.size(); i++){
        lights.at(i)->uboPosition --;
        lights.at(i)->uploadToGpu();
    }
}

PointLight::~PointLight() {
    reassignPositions(this->uboPosition);
}