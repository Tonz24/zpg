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
    explicit Scale(const glm::vec3& scale = {0,0,0}) : scale(scale){}
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