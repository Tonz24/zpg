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

            // back face
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 7
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 6
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 4
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 6
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 5
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  // Vertex 4

            // right face
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 1
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 5
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 2
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 5
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 6
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   // Vertex 2

            // left face
            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 3
            -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 7
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 4

            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 3
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 4
            -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  // Vertex 0

            // top face
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 3
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 2
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 6
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 3
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 6
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   // Vertex 7

            // bottom face
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 5
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 1
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 0

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,   // Vertex 4
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 5
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  // Vertex 0
    };
};


