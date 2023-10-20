//
// Created by Tonz on 20.10.2023.
//

#include "PostFX.h"

PostFX &PostFX::getInstance() {
    if (instance == nullptr)
        instance = new PostFX();
    return *instance;
}

void PostFX::applyEffects() {
    for (auto& effect : this->effects){
        this->pingPongs[pong]->bind();
        glClear(GL_COLOR_BUFFER_BIT);
        effect.apply();

        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pingPongs[ping]->getTargetId());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        std::swap(ping,pong);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->pingPongs[ping]->getTargetId());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostFX::bindPing() {
    this->pingPongs[ping]->bind();
}

void PostFX::bindPong() {
    this->pingPongs[pong]->bind();
}

PostFX::PostFX() {
    this->initialize();
}

void PostFX::initialize() {
    this->pingPongs[0] = new Framebuffer();
    this->pingPongs[1] = new Framebuffer();

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void PostFX::addEffect(ImageEffect effect) {
    this->effects.push_back(effect);
}