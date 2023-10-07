//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include <glm/glm.hpp>
#include "VertexType.h"

struct Vertex{
    Vertex(glm::vec3 pos = glm::vec3{0,0,0}, glm::vec3 color = glm::vec3{0,0,0}, glm::vec3 normal = glm::vec3{0,0,0}, glm::vec2 uv = glm::vec2{0,0})
        : pos(pos),color(color),normal(normal),uv(uv){}

    Vertex(const std::vector<float>& values, const std::vector<VertexElement*>& types){

        int valuesRead{0};
        for (int i = 0; i < types.size(); i++){
            int offset = types[i]->getElementOffset();

            int count = types[i]->getElementCount();
            for (int j = 0; j < count; j++){
                (*this)[offset + j] = values[valuesRead++];
                if (valuesRead >= values.size()) return;
            }
        }
    }

    glm::vec3 pos{0};
    glm::vec3 normal{0};
    glm::vec3 color{1};
    glm::vec2 uv{0};

    inline float &operator[](const uint32_t &index) {
        if (index < 3) return this->pos[index];
        if (index < 6) return this->normal[index - 3];
        if (index < 9) return this->color[index - 6];
        if (index < 11) return this->color[index - 9];
        else exit(1);
    }
};


