//
// Created by Tonz on 19.10.2023.
//

#include "ImageEffect.h"
#include "../Application.h"

ImageEffect::ImageEffect(const glm::vec3& filter) : shader(*Shader::getShaderProgram("shader_fbo")), filter(filter) {
}

void ImageEffect::apply() {
    this->shader.use();
    this->shader.setFloat("time",Application::getInstance().getTime());
    this->shader.setVec3f("filter",this->filter);
}