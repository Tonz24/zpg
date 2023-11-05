//
// Created by Tonz on 31.10.2023.
//

#pragma once
#include "Material.h"
#include "../Texture.h"

class FurMaterial : public Material{
public:
    void uploadVariables() override;

    explicit FurMaterial(int layerCount = 10, float height = 0.1f, const glm::vec2& gridDimensions = {100, 100});

    void setObjectColor(const glm::vec3 &objectColor) override;

private:
    int layerCount{10};
    float height{0.1f};
    glm::vec2 gridDimensions{100,100};
    std::shared_ptr<Texture> noiseTexture = std::make_shared<Texture>(R"(noise.png)");
};