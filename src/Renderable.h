//
// Created by Tonz on 03.10.2023.
//

#pragma once
#include <functional>

#include "Model.h"
#include "Material.h"
#include "Transformation.h"
#include "InputManager.h"
#include "Cube.h"

#include "ITickable.h"
#include "IDrawable.h"

class Renderable : public ITickable, public IDrawable {
public:
    explicit Renderable(Model* model = new Cube(), Material* m = new Material(), Transformation* transformation = new TransformationComposite());

    virtual void draw() override;

    void tick() override;

    virtual ~Renderable() = default;

protected:
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
    std::shared_ptr<Transformation> transform;
    //std::shared_ptr<Controller> controller;

    Rotation * rotation;

    glm::mat4 modelMat{1};

    void uploadModelMatrix();
};