//
// Created by Tonz on 07.10.2023.
//

#include "Cube.h"


Cube::Cube() : Model() {
        this->vertexDescription = {new PosElement(), new NorElement(), new UvElement()};
        for(int i = 0; i < cubeData.size(); i+= 8){
            Vertex v{{cubeData[i],cubeData[i+1],cubeData[i+2],cubeData[i+3],cubeData[i+4],cubeData[i+5],cubeData[i+6],cubeData[i+7]},this->vertexDescription};
            this->vertices.push_back(v);
        }
        this->init();
}
