//
// Created by Tonz on 06.10.2023.
//

#pragma once

#include "Transformation.h"

class Controller {
public:

    Controller(const float& movementSpeed = 100.0f,const float& rotationSpeed = 1000.0f);

    void applyPreTransform(glm::mat4& matrix);
    void applyPostTransform(glm::mat4& matrix);

private:

    float movementSpeed;
    float rotationSpeed{1.0f};

    std::unique_ptr<TransformationComposite> preTransform{};
    std::unique_ptr<TransformationComposite> postTransform{};
    Translation* translation{};
    Rotation* rotationX{};
    Rotation* rotationY{};
    Rotation* rotationZ{};
};