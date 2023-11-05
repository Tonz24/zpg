//
// Created by Tonz on 31.10.2023.
//

#include "Quad.h"

Quad::Quad() {
    this->vertexDescription = {new PosElement(), new NorElement(), new UvElement()};
    for(int i = 0; i < quadData.size(); i+= 8){
        Vertex v{{quadData[i],quadData[i+1],quadData[i+2],quadData[i+3],quadData[i+4],quadData[i+5],quadData[i+6],quadData[i+7]},this->vertexDescription};
        this->vertices.push_back(v);
    }
    this->init();
}
