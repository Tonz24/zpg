//
// Created by Tonz on 20.10.2023.
//

#include "GaussianBlur.h"

void GaussianBlur::apply() {
    ImageEffect::apply();
}

GaussianBlur::GaussianBlur() : ImageEffect("effect_blur_horizontal") {
}