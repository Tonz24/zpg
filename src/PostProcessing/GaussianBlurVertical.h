//
// Created by Tonz on 20.10.2023.
//

#pragma once


#include "ImageEffect.h"

class GaussianBlurVertical : public ImageEffect {
public:
    GaussianBlurVertical() : ImageEffect("effect_blur_vertical"){}

    void apply() override {
        ImageEffect::apply();
    }
};
