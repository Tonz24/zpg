//
// Created by Tonz on 03.10.2023.
//

#pragma once
#include <functional>

#include "Models/Model.h"
#include "Materials/ConstantMaterial.h"
#include "Transformation.h"
#include "InputManager.h"
#include "Models/Cube.h"

#include "ITickable.h"
#include "IDrawable.h"

class SceneObject : public ITickable, public IDrawable {
public:
    explicit SceneObject(Model* model = nullptr, Material* m = new ConstantMaterial());
    explicit SceneObject(const std::string& path);

    virtual void draw() override;
    virtual void drawForShadowMapping() override;
    void tick() override;

    [[nodiscard]] const Material &getMaterial() const override;

    virtual ~SceneObject() = default;

    virtual void setTranslation(const glm::vec3& translation);
    virtual void translate(const glm::vec3& translation);
    virtual void setRotation(const float& angle,const glm::vec3& axis);
    virtual void rotate(const float& angle);
    virtual void setScale(const glm::vec3& scale);
    virtual void setRotateAround(float angle, const glm::vec3& point, const glm::vec3& axis);
    virtual void rotateAround(float angle);

    [[nodiscard]] const glm::vec3& getTranslation() const;

    void addChild(std::unique_ptr<SceneObject> child){
        this->children.push_back(std::move(child));
    }

    void applyTransform();

    [[nodiscard]] const glm::mat4& getModelMat() const override{
        return this->modelMat;
    }

    [[nodiscard]] const bool& canCastRays() const override{
        return this->castRays;
    }

    void setCanCastRays(bool value) override{
        this->castRays = value;
    }

protected:
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
    std::unique_ptr<TransformationComposite> transform;
    RotateAroundPoint* rotateAroundPoint;
    Translation* translation;
    Rotation* rotation;
    Scale* scale;

    glm::mat4 modelMat{1};

    void applyTransform(const glm::mat4& modelMat);
    std::vector<std::unique_ptr<SceneObject>> children{};

    void uploadModelMatrix();

    bool castRays{false};
};