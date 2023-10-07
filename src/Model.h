//
// Created by Tonz on 26.09.2023.
//
#pragma once

#include <vector>
#include <memory>

#include "GL/glew.h"
#include "Vertex.h"
#include "VertexType.h"


class Model {
public:
    ~Model();
    virtual void draw();

protected:
    Model(std::vector<VertexElement*> types);
    Model();

    std::vector<VertexElement*> vertexDescription;

    uint32_t vbo{0};
    uint32_t vao{0};

    std::vector<Vertex> vertices{};

    void init();
};