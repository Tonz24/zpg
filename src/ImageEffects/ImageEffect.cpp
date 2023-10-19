//
// Created by Tonz on 19.10.2023.
//

#include "ImageEffect.h"
#include "../Application.h"

ImageEffect::ImageEffect(const std::string& shader) : shader(Shader::getShaderProgram(shader)) {
}

void ImageEffect::apply() {
    this->shader->use();
    this->shader->setFloat("time",Application::getInstance().getTime());
}