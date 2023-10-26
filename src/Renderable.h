//
// Created by Tonz on 03.10.2023.
//

#pragma once
#include <functional>

#include "Model.h"
#include "Materials/ConstantMaterial.h"
#include "Transformation.h"
#include "InputManager.h"
#include "Cube.h"

#include "ITickable.h"
#include "IDrawable.h"

class Renderable : public ITickable, public IDrawable {
public:
    explicit Renderable(Model* model = nullptr, ConstantMaterial* m = new ConstantMaterial());

    virtual void draw() override;
    virtual void drawForShadowMapping() override;
    void tick() override;

    const ConstantMaterial &getMaterial() const override;

    virtual ~Renderable() = default;

    virtual void setTranslation(const glm::vec3& translation);
    virtual void translate(const glm::vec3& translation);
    virtual void setRotation(const float& angle,const glm::vec3& axis);
    virtual void rotate(const float& angle);
    virtual void setScale(const glm::vec3& scale);
    virtual void setRotateAround(float angle, const glm::vec3& point, const glm::vec3& axis);
    virtual void rotateAround(float angle);

protected:
    std::shared_ptr<Model> model;
    std::shared_ptr<ConstantMaterial> material;
    std::unique_ptr<TransformationComposite> transform;
    RotateAroundPoint* rotateAroundPoint;
    Translation* translation;
    Rotation* rotation;
    Scale* scale;

    glm::mat4 modelMat{1};

    void applyTransform();
    void uploadModelMatrix();
};