//
// Created by Tonz on 20.10.2023.
//

#pragma once


#include "ImageEffect.h"

class GaussianBlur : public ImageEffect {
public:
    GaussianBlur();
    void apply() override;

};


