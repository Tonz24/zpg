//
// Created by Tonz on 07.10.2023.
//

#include "Cube.h"


Cube::Cube() : Model() {
        for(int i = 0; i < cubeData.size(); i+= 6){
            Vertex v{{cubeData[i],cubeData[i+1],cubeData[i+2],cubeData[i+3],cubeData[i+4],cubeData[i+5]},this->vertexDescription};
            this->vertices.push_back(v);
        }
        this->init();
}
