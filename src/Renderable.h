//
// Created by Tonz on 03.10.2023.
//

#pragma once
#include <functional>

#include "Model.h"
#include "Material.h"
#include "Transformation.h"
#include "InputManager.h"
#include "Controller.h"

class Renderable {
public:
    Renderable(Model* model, Material* material, TransformationComposite* transformation, Controller* controller = nullptr);

        void draw();
private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
    std::shared_ptr<TransformationComposite> transform;
    std::shared_ptr<Controller> controller;

    Rotation * rotation;

    glm::mat4 modelMat{1};

    void uploadModelMatrix();

    inline static uint32_t uboId{0};
    inline static bool uboInitialized{false};
    static constexpr uint32_t UBO_BINDING_POINT{5};

    static void initUBO();

};