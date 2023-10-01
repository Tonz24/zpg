//
// Created by Tonz on 30.09.2023.
//

#include "Transform.h"
#include "ext/matrix_transform.hpp"

void Transform::setPosition(const glm::vec3 &position) {
    this->translation = position;
    applyTransform();
}

void Transform::translate(const glm::vec3 &translation) {
    this->translation += translation;
    applyTransform();
}

void Transform::rotate(const float &angle, const Rotation_Axis &axis) {
    switch (axis) {
        case AXIS_X:
            this->rotation.x += angle;
            break;
        case AXIS_Y:
            this->rotation.y += angle;
            break;
        case AXIS_Z:
            this->rotation.z += angle;
            break;
    }
    applyTransform();
}

void Transform::rotate(const glm::vec3& rotation) {
    this->rotation += rotation;
    applyTransform();
}

void Transform::setRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
    applyTransform();
}

void Transform::setScale(const glm::vec3 &scale) {
    this->scale = scale;
    applyTransform();
}

void Transform::applyTransform() {
    glm::mat4 newModelMat{1.0f};

    newModelMat = glm::translate(newModelMat,this->translation);

    newModelMat = glm::rotate(newModelMat,glm::radians(rotation.x),{1,0,0});
    newModelMat = glm::rotate(newModelMat,glm::radians(rotation.y),{0,1,0});
    newModelMat = glm::rotate(newModelMat,glm::radians(rotation.z),{0,0,1});

    newModelMat = glm::scale(newModelMat,this->scale);

    this->modelMat = newModelMat;
}

const glm::mat4x4 &Transform::getModelMat() const {
    return this->modelMat;
}


