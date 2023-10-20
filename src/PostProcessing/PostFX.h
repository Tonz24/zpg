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
    void bindPing();
    void bindPong();
    void swapValues();
    void drawToTarget();

private:
    PostFX();
    void initialize();

    inline static PostFX* instance{nullptr};
    Framebuffer* pingPongs[2]{};

    std::vector<std::unique_ptr<ImageEffect>> effects{};
    std::unique_ptr<ImageEffect> finalRender;

    uint32_t quadVBO{0};
    uint32_t quadVAO{0};

    int ping{0}, pong{1};

    const float quadVertices[24] = {
            -1.0f,  1.0f,       0.0f, 1.0f,
            -1.0f, -1.0f,       0.0f, 0.0f,
            1.0f, -1.0f,        1.0f, 0.0f,

            -1.0f,  1.0f,       0.0f, 1.0f,
            1.0f, -1.0f,        1.0f, 0.0f,
            1.0f,  1.0f,        1.0f, 1.0f
    };
};