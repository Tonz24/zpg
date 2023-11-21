//
// Created by Tonz on 11.11.2023.
//

#pragma once

#include "Material.h"
#include "../Texture.h"

class PBMaterial : public Material {
public:

    PBMaterial(const glm::vec3 &albedo, float roughness, float metallic);

    void uploadVariables() override;

    void setObjectColor(const glm::vec3 &objectColor) override;

    void setTextures(std::shared_ptr<Texture> albedoMap, std::shared_ptr<Texture> roughnessMap, std::shared_ptr<Texture> metallicMap, std::shared_ptr<Texture> aoMap);

private:
    glm::vec3 albedo{1};
    float roughness{0.3};
    float metallic{0.3};
    glm::vec3 emissive{0};

    std::shared_ptr<Texture> albedoMap;
    std::shared_ptr<Texture> roughnessMap;
    std::shared_ptr<Texture> metallicMap;
    std::shared_ptr<Texture> aoMap;
};