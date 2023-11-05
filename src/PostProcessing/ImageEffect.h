//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "../ShaderProgram.h"

class ImageEffect {
public:
    virtual void apply();

protected:
    virtual void uploadValues();

    explicit ImageEffect(const std::string& shader);
    explicit ImageEffect() = default;
    const ShaderProgram* shader;
};


