//
// Created by Tonz on 30.09.2023.
//

#include <GL/glew.h>
#include "Transform.h"
#include "ext/matrix_transform.hpp"

void Transform::setPosition(const glm::vec3 &position) {
    this->translation = position;
    changed = true;
}

void Transform::translate(const glm::vec3 &translation) {
    this->translation += translation;
    changed = true;
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
    changed = true;
}

void Transform::rotate(const glm::vec3& rotation) {
    this->rotation += rotation;
    changed = true;
}

void Transform::setRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
    changed = true;
}

void Transform::setRotation(const float &angle, const Rotation_Axis &axis) {
    switch (axis) {
        case AXIS_X:
            this->rotation.x = angle;
            break;
        case AXIS_Y:
            this->rotation.y = angle;
            break;
        case AXIS_Z:
            this->rotation.z = angle;
            break;
    }
    changed = true;
}

void Transform::setScale(const glm::vec3 &scale) {
    this->scale = scale;
    changed = true;
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

const glm::mat4x4 &Transform::getModelMat(){
    if (this->changed)
        this->applyTransform();
    this->changed = false;
    return this->modelMat;
}

void Transform::uploadToGpu() {
    uploadToGpuInternal(*this);
}

void Transform::uploadToGpuInternal(Transform& transform) {
    if (!uboInitialized)
        initUBO();

    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBindBufferBase(GL_UNIFORM_BUFFER, BINDING_POINT, uboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 4*4*4, &transform.getModelMat());
}

void Transform::initUBO() {
    glGenBuffers(1, &uboId);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBufferData(GL_UNIFORM_BUFFER, 4*4*4, NULL, GL_STATIC_DRAW); //TODO: test whether GL_DYNAMIC_DRAW is faster
    uboInitialized = true;
}