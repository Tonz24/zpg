//
// Created by Tonz on 20.10.2023.
//

#include "EmptyEffect.h"

void EmptyEffect::apply() {
    if (this->shader != nullptr) {
        glDisable(GL_BLEND);

        PostFX& instance = PostFX::getInstance();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        this->shader->bind();

        glViewport(0, 0, 1920, 1080);
        instance.drawToTarget(0);
        instance.swapValues();
    }
}