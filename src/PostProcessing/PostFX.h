//
// Created by Tonz on 20.10.2023.
//

#pragma once


#include "../Framebuffer.h"
#include "ImageEffect.h"

class PostFX {
public:

    static PostFX& getInstance();

    void addEffect(ImageEffect* effect);
    void applyEffects();
    void swapValues();
    void drawToTarget(int mipLevel = 0);
    void drawToTargetFromOcclusionFBO();

    void bindPing(int mipLevel = 0);
    void bindPong(int mipLevel = 0);
    const Framebuffer& getPing();
    const Framebuffer& getPong();

    std::unique_ptr<Framebuffer> occlusionMap;
    const ShaderProgram* occlusionMapShader;

private:
    PostFX();
    void initialize();

    inline static PostFX* instance{nullptr};
    Framebuffer* pingPongBuffers[2];


    std::vector<std::unique_ptr<ImageEffect>> effects{};
    std::unique_ptr<ImageEffect> finalRender;

    uint32_t quadVBO{0};
    uint32_t quadVAO{0};

    int ping{0},pong{1};

    const float quadVertices[24] = {
            -1.0f,  1.0f,       0.0f, 1.0f,
            -1.0f, -1.0f,       0.0f, 0.0f,
            1.0f, -1.0f,        1.0f, 0.0f,

            -1.0f,  1.0f,       0.0f, 1.0f,
            1.0f, -1.0f,        1.0f, 0.0f,
            1.0f,  1.0f,        1.0f, 1.0f
    };
};