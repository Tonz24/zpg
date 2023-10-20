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
        PostFX& instance = PostFX::getInstance();
        instance.bindPong();
        glClear(GL_COLOR_BUFFER_BIT);

        this->shader->use();
        this->uploadValues();

        instance.drawToTarget();
        instance.swapValues();
    }
}

void ImageEffect::uploadValues() {
    this->shader->setFloat("time", Application::getInstance().getTime());
}