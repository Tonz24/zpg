//
// Created by Tonz on 20.10.2023.
//

#pragma once


#include "ImageEffect.h"

class GaussianBlur : public ImageEffect {
public:
    GaussianBlur() : ImageEffect(){}

    void apply() override {
        this->horizontal.apply();
        this->vertical.apply();
    }

private:
    class GaussianBlurHorizontal : public ImageEffect{
    public:
        GaussianBlurHorizontal() : ImageEffect("effect_gaussian_blur_horizontal") {}
    };

    class GaussianBlurVertical : public ImageEffect{
    public:
        GaussianBlurVertical() : ImageEffect("effect_gaussian_blur_vertical") {}
    };

    GaussianBlurHorizontal horizontal;
    GaussianBlurVertical vertical;
};