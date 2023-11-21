//
// Created by Tonz on 12.11.2023.
//

#pragma once


#include <string>
#include "IDrawable.h"
#include "Materials/Material.h"
#include "Models/Model.h"

class Skybox : public IDrawable {
public:
    explicit Skybox(const std::string& path);

    void draw() override;
    void drawForShadowMapping() override;
    const Material &getMaterial() const override;
    const bool &canCastRays() const override;
    void setCanCastRays(bool value) override;
    const glm::mat4 &getModelMat() const override;

private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Model> model;

    glm::mat4 dummy{1};
    bool dummmy{false};
};


