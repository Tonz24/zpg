//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "ImageEffect.h"
#include "PostFX.h"

class EmptyEffect : public ImageEffect {
public:
    EmptyEffect() : ImageEffect("effect_empty") {}

    void apply() override {
        if (this->shader != nullptr) {
            PostFX& instance = PostFX::getInstance();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            this->shader->use();

            instance.drawToTarget();
            instance.swapValues();
        }
    }
};