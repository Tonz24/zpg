//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "ImageEffect.h"
#include "PostFX.h"

class EmptyEffect : public ImageEffect {
public:
    EmptyEffect() : ImageEffect("effect_empty") {}

    void apply() override;
};


