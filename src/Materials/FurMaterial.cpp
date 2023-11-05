//
// Created by Tonz on 31.10.2023.
//

#include "FurMaterial.h"
#include "../Application.h"

void FurMaterial::uploadVariables() {
    Material::uploadVariables();
    this->shader.setVar("gridDimensions",this->gridDimensions);
    this->shader.setVar("layerCount",this->layerCount);
    this->shader.setVar("time",Application::getInstance().getTime());
    this->shader.setVar("layerOffset",this->height / static_cast<float>(this->layerCount));
    this->noiseTexture->bind(0);
}

FurMaterial::FurMaterial(int layerCount, float height, const glm::vec2& gridDimensions): Material("shader_fur"),
                                                                                         layerCount(layerCount), height(height), gridDimensions(gridDimensions) {}

void FurMaterial::setObjectColor(const glm::vec3 &objectColor) {

}
