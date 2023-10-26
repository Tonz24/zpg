//
// Created by Tonz on 06.10.2023.
//

#pragma once
#include <GL/glew.h>

#include <vector>
#include <memory>

#include "glm.hpp"
#include "ext/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Transformation {
public:
    virtual void apply(glm::mat4& matrix) const = 0;
    virtual ~Transformation() = default;
};

class Translation : public Transformation{
public:
    explicit Translation(const glm::vec3& translation = {0,0,0}) : translation(translation){}
    void apply(glm::mat4 &matrix) const override;

    void setTranslation(const glm::vec3& newTranslation);
    void translate(const glm::vec3& newTranslation);

    const glm::vec3 &getTranslation() const {
        return translation;
    }

private:
    glm::vec3 translation{0};
};

class Rotation : public Transformation{
public:
    explicit Rotation(const float& angle = 0,const glm::vec3& axis = {0,1,0}) : angle(angle), axis(glm::normalize(axis)){}
    void apply(glm::mat4 &matrix) const override;

    void setRotation(const float& angle,const glm::vec3& axis);
    void rotate(const float& angle);

    [[nodiscard]] const float& getAngle() const;

private:
    float angle{0};
    glm::vec3 axis{0,1,0};
};

class Scale : public Transformation{
public:
    explicit Scale(const glm::vec3& scale = {1,1,1}) : scale(scale){}
    void apply(glm::mat4 &matrix) const override;

    void setScale(const glm::vec3& newScale);

private:
    glm::vec3 scale{1};
};

class TransformationComposite : public Transformation{
public:
    TransformationComposite() = default;
    TransformationComposite(std::initializer_list<Transformation*> transformations);
    void addTransformation(Transformation* transformation);
    void addTransformation(const std::vector<Transformation*>& transformations);
    void apply(glm::mat4& matrix) const override;

private:
    std::vector<std::unique_ptr<Transformation>> transformations{};
};

class RotateAroundPoint : public Transformation{
public:
    explicit RotateAroundPoint(float angle = 0, const glm::vec3 &point = {0,0,0}, const glm::vec3 &axis = {0,1,0}):
        angle(angle), point(point),axis(axis) {}

    void apply(glm::mat4 &matrix) const override {
        glm::mat4 trans = glm::translate(glm::mat4{1},-this->point);
        glm::mat4 rot = glm::rotate(glm::mat4{1},glm::radians(this->angle),this->axis);
        glm::mat4 back = glm::translate(glm::mat4{1},this->point);
        matrix = back * rot * trans * matrix;
    }

    void setRotation(float angle) {
        this->angle = angle;
    }

    void rotate(float angle) {
        this->angle += angle;
    }

    void setPoint(const glm::vec3 &point) {
        this->point = point;
    }

    void setAxis(const glm::vec3 &axis) {
        this->axis = glm::normalize(axis);
    }

private:
    float angle{10};
    glm::vec3 point{0};
    glm::vec3 axis{0,1,0};
};