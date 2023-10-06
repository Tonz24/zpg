//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include "Model.h"



class Quad : public Model{
public:
    explicit Quad(Material& material);
    Quad(glm::vec3 translation, Material& material);

private:
    static inline std::vector<Vertex> quadData = {
            {.pos = {-0.15f,-0.15f, 0.f},   .color={1,0,0}, .uv={0,0}},
            {.pos = {-0.15f , 0.15f , 0.f}, .color={1,0,0}, .uv={0,1}},
            {.pos = {0.15f , -0.15f, 0.f},  .color={1,0,0}, .uv={1,0}},

            {.pos = {-0.15f,0.15f, 0.f},    .color={1,0,0}, .uv={0,1}},
            {.pos = {0.15f , 0.15f , 0.f},  .color={1,0,0}, .uv={1,1}},
            {.pos = {0.15f , -0.15f, 0.f},  .color={1,0,0}, .uv={1,0}}};
};


