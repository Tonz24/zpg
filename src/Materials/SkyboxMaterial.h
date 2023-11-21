//
// Created by Tonz on 07.11.2023.
//

#pragma once


#include "Material.h"
#include "../Texture.h"

class SkyboxMaterial : public Material {
public:
    explicit SkyboxMaterial(const std::string& path);

    void setObjectColor(const glm::vec3 &objectColor) override;

    void uploadVariables() override;

private:
    std::shared_ptr<Texture> skybox;

    inline static std::vector<std::string> faces{"right.jpg",
                                                 "left.jpg",
                                                 "top.jpg",
                                                 "bottom.jpg",
                                                 "front.jpg",
                                                 "back.jpg"};
};