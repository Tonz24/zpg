//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include <glm/glm.hpp>

struct Vertex{
    Vertex(glm::vec3 pos = glm::vec3{0,0,0}, glm::vec3 color = glm::vec3{0,0,0}, glm::vec3 normal = glm::vec3{0,0,0}, glm::vec2 uv = glm::vec2{0,0})
        : pos(pos),color(color),normal(normal),uv(uv){}
    glm::vec3 pos{0};
    glm::vec3 normal{0};
    glm::vec3 color{1};
    glm::vec2 uv{0};
};