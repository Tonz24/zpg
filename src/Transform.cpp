//
// Created by Tonz on 30.09.2023.
//

#include <GL/glew.h>
#include "Transform.h"
#include "ext/matrix_transform.hpp"

void Transform::setPosition(const glm::vec3 &position) {
    this->translation = position;
}

void Transform::translate(const glm::vec3 &translation) {
    this->translation += translation;
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
}

void Transform::rotate(const glm::vec3& rotation) {
    this->rotation += rotation;
}

void Transform::setRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
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
}

void Transform::setScale(const glm::vec3 &scale) {
    this->scale = scale;
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
    this->applyTransform();
    return this->modelMat;
}

void Transform::uploadToGpu() {
    uploadToGpuInternal(*this);
}

void Transform::uploadToGpuInternal(Transform& transform) {
    if (!uboInitialized)
        initUBO();

    TransformShaderFormat format = transform.getShaderFormat();
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBindBufferBase(GL_UNIFORM_BUFFER, BINDING_POINT, uboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 112, &format);
}

void Transform::initUBO() {
    glGenBuffers(1, &uboId);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBufferData(GL_UNIFORM_BUFFER, 112, NULL, GL_STATIC_DRAW); //TODO: test whether GL_DYNAMIC_DRAW is faster
    uboInitialized = true;
}

TransformShaderFormat Transform::getShaderFormat(){
    return TransformShaderFormat{.translation = this->translation, .rotation = this->rotation, .scale = this->scale, .modelMat =this->getModelMat()};
}