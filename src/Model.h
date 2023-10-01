//
// Created by Tonz on 26.09.2023.
//
#pragma once

#include "Shader.h"
#include "Vertex.h"
#include "Material.h"
#include "Transform.h"

class Model {
public:
    ~Model();

    void draw();
    Transform& getTransform();

protected:
    Model(std::vector<Vertex>& vertices, Material& material);
    Model(std::vector<Vertex>& vertices, Material& material, glm::vec3& translation);
    Model() = delete;

    Material& material;

    GLuint vbo{0};
    GLuint vao{0};

    glm::vec3 translation{0};

    Transform transform;

    std::vector<Vertex> vertices;

    void init();
};