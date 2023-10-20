//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "../Shader.h"

class ImageEffect {
public:
    virtual void apply();

protected:
    virtual void uploadValues();

    explicit ImageEffect(const std::string& shader);
    explicit ImageEffect() = default;
    const Shader* shader;
};


