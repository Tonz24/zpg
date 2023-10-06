//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include "Model.h"

class Triangle : public Model{
public:
    explicit Triangle(Material& material);
    Triangle(glm::vec3 translation, Material& material);

private:
static inline std::vector<Vertex> triangleData = {
        {.pos = {-0.15f, -0.15f,0.f},   .color={1, 0, 0},   .uv={0,0}},
        {.pos = {-0.15f, 0.15f, 0.f},   .color={1, 0, 0},   .uv={0,1}},
        {.pos = {0.15f, -0.15f, 0.f},   .color={1, 0, 0},   .uv={1,0}},
    };
};