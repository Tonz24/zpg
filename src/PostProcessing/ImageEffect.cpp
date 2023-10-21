//
// Created by Tonz on 19.10.2023.
//

#include "ImageEffect.h"
#include "../Application.h"
#include "PostFX.h"


ImageEffect::ImageEffect(const std::string& shader) : shader(Shader::getShaderProgram(shader)) {
}

void ImageEffect::apply() {
    if (this->shader != nullptr) {
        glDisable(GL_BLEND);
        PostFX& instance = PostFX::getInstance();
        instance.bindPong();

        this->shader->use();
        this->uploadValues();

        instance.drawToTarget();
        instance.swapValues();
    }
}

void ImageEffect::uploadValues() {
    this->shader->setFloat("time", Application::getInstance().getTime());
}