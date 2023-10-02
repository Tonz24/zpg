//
// Created by Tonz on 30.09.2023.
//

#pragma once
#include "glm.hpp"

enum Rotation_Axis{
    AXIS_X,
    AXIS_Y,
    AXIS_Z
};

struct TransformShaderFormat{

    const glm::vec3 translation;
    float padding{0};
    const glm::vec3 rotation;
    float padding2{0};
    const glm::vec3 scale;
    float padding3{0};
    const glm::mat4x4 modelMat;
};

class Transform {
public:

    void translate(const glm::vec3& translation);
    void setPosition(const glm::vec3& position);

    void rotate(const float& angle,const Rotation_Axis& axis);
    void rotate(const glm::vec3& rotation);

    void setRotation(const glm::vec3& rotation);
    void setRotation(const float& angle,const Rotation_Axis& axis);

    void setScale(const glm::vec3& scale);

    [[nodiscard]] const glm::mat4x4& getModelMat() const;

    void uploadToGpu();
    [[nodiscard]] TransformShaderFormat getShaderFormat() const;

private:
    glm::vec3 translation{0};
    glm::vec3 rotation{0};
    glm::vec3 scale{1};

    glm::mat4x4 modelMat{1};

    void applyTransform();

    inline static uint32_t uboId{0};
    inline static bool uboInitialized{false};

    static void initUBO();
    static void uploadToGpuInternal(const Transform& transform);

    constexpr inline static uint32_t BINDING_POINT{5};
};