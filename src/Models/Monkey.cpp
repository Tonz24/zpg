//
// Created by Tonz on 07.10.2023.
//

#include "Monkey.h"

Monkey::Monkey() : Model() {
    for(int i = 0; i < suziSmooth.size(); i+= 6){
        Vertex v{{suziSmooth[i],suziSmooth[i+1],suziSmooth[i+2],suziSmooth[i+3],suziSmooth[i+4],suziSmooth[i+5]},this->vertexDescription};
        this->vertices.push_back(v);
    }
    this->init();
}
