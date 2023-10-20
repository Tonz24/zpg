//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "ImageEffect.h"

class EmptyEffect : public ImageEffect {
public:
    EmptyEffect();
    void apply() override;

private:
};


