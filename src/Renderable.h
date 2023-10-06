//
// Created by Tonz on 03.10.2023.
//

#pragma once

#include "Model.h"
#include "Material.h"
#include "Transform.h"

class Renderable {
public:
    Renderable(Model* model, Material* material)
        : model(std::shared_ptr<Model>(model)), material(std::shared_ptr<Material>(material)){}

        void draw();

        Transform& getTransform(){
            return transform;
        }
private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
    Transform transform{};
};