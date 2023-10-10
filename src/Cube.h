//
// Created by Tonz on 07.10.2023.
//

#pragma once


#include "Model.h"

class Cube : public Model {
public:
    Cube();
private:
    static inline const std::vector<float> cubeData = {
            // front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // Vertex 0
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // Vertex 1
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // Vertex 2
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // Vertex 0
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // Vertex 2
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   // Vertex 3

            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 4
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 5
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 6
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 4
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 6
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 7

            // right face
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 1
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 5
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 2
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 5
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 6
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 2

            // Left face
            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 3
            -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 0
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 4

            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 3
            -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 7
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 4

            // Top face
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 3
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 2
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 6
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 3
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 6
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 7

            // Bottom face
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 0
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 1
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 5
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 0
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 5
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f   // Vertex 4
    };
};


