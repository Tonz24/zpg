//
// Created by Tonz on 20.10.2023.
//

#include "PostFX.h"
#include "EmptyEffect.h"

PostFX &PostFX::getInstance() {
    if (instance == nullptr)
        instance = new PostFX();
    return *instance;
}

void PostFX::applyEffects() {
    for (auto& effect : this->effects){
        effect->apply();
    }
    this->finalRender->apply();
}

PostFX::PostFX() {
    this->initialize();
}

void PostFX::initialize() {
    this->finalRender = std::make_unique<EmptyEffect>();

    this->pingPongBuffers[0] = new Framebuffer(10);
    this->pingPongBuffers[1] = new Framebuffer(10);
    this->occlusionMap = std::make_unique<Framebuffer>();
    this->occlusionMapShader = ShaderProgram::getShaderProgram("shader_occlusion");

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

void PostFX::addEffect(ImageEffect* effect) {
    this->effects.push_back(std::unique_ptr<ImageEffect>(effect));
}

void PostFX::swapValues() {
    std::swap(ping,pong);
}

void PostFX::drawToTarget(int mipLevel) {
    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->getPing().getTargetId(mipLevel));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostFX::drawToTargetFromOcclusionFBO() {
    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->occlusionMap->getTargetId(0));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostFX::bindPing(int mipLevel) {
    this->pingPongBuffers[ping]->bind(mipLevel);
}

void PostFX::bindPong(int mipLevel) {
    this->pingPongBuffers[pong]->bind(mipLevel);
}

const Framebuffer &PostFX::getPing() {
    return *this->pingPongBuffers[ping];
}

const Framebuffer &PostFX::getPong() {
    return *this->pingPongBuffers[pong];
}