//
// Created by Tonz on 06.10.2023.
//

#include "Transformation.h"

void Translation::apply(glm::mat4 &matrix) const {
    matrix = glm::translate(matrix,translation);
}

void Translation::setTranslation(const glm::vec3& newTranslation) {
    this->translation = newTranslation;
}

void Translation::translate(const glm::vec3 &newTranslation) {
    this->translation += newTranslation;
}

void Rotation::apply(glm::mat4 &matrix) const {
    matrix = glm::rotate(matrix,glm::radians(angle),axis);
}

void Rotation::setRotation(const float& angle,const glm::vec3& axis) {
    this->angle = angle;
    this->axis = axis;
}

const float &Rotation::getAngle() const {
    return this->angle;
}

void Rotation::rotate(const float &angle) {
    this->angle += angle;
}

void Scale::apply(glm::mat4 &matrix) const {
    matrix = glm::scale(matrix,scale);
}

void Scale::setScale(const glm::vec3 &newScale) {
    this->scale = newScale;
}

void TransformationComposite::addTransformation(Transformation *transformation) {
    transformations.push_back(std::unique_ptr<Transformation>(transformation));
}

void TransformationComposite::apply(glm::mat4 &matrix) const {
    for (const auto& transformation : transformations) {
        transformation->apply(matrix);
    }
}

TransformationComposite::TransformationComposite(std::initializer_list<Transformation *> transformations) {
    for (const auto &item : transformations){
        this->transformations.push_back(std::unique_ptr<Transformation>(item));
    }
}

void TransformationComposite::addTransformation(const std::vector<Transformation*>& transformations) {
    for (const auto &item : transformations){
        this->transformations.push_back(std::unique_ptr<Transformation>(item));
    }
}
