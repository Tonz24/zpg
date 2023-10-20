//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "ImageEffect.h"

class ColorFilter : public ImageEffect {
public:
    ColorFilter(const glm::vec3& filter = {1,1,1});

protected:
    void uploadValues() override;

private:
    glm::vec3 filter{1,1,1};
};


