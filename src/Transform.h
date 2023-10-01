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

class Transform {
public:

    void translate(const glm::vec3& translation);
    void setPosition(const glm::vec3& position);

    void rotate(const float& angle,const Rotation_Axis& axis);
    void rotate(const glm::vec3& rotation);
    void setRotation(const glm::vec3& rotation);

    void setScale(const glm::vec3& scale);

    [[nodiscard]] const glm::mat4x4& getModelMat() const;

private:
    glm::vec3 translation{0};
    glm::vec3 rotation{0};
    glm::vec3 scale{1};

    glm::mat4x4 modelMat{1};

    void applyTransform();
};