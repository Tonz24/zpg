//
// Created by Tonz on 20.10.2023.
//

#pragma once


#include "ImageEffect.h"

class BoxBlur : public ImageEffect {
public:
    BoxBlur() : ImageEffect(){}

    void apply() override {
        this->horizontal.apply();
        this->vertical.apply();
    }

private:
    class BoxBlurHorizontal : public ImageEffect{
    public:
        BoxBlurHorizontal() : ImageEffect("effect_box_blur_horizontal") {}
    };

    class BoxBlurVertical : public ImageEffect{
    public:
        BoxBlurVertical() : ImageEffect("effect_box_blur_vertical") {}
    };

    BoxBlurHorizontal horizontal;
    BoxBlurVertical vertical;
};