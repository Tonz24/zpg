//
// Created by Tonz on 28.10.2023.
//

#include "Bush.h"

void Bush::fillVector() {
    bushData.insert(bushData.end(), &bushes[0], &bushes[54210 - 1]);
    vectorFilled = true;
}

Bush::Bush() {
    if (!vectorFilled) fillVector();

    for(int i = 0; i < 54210 - 6; i+= 6){
        Vertex v{{bushData[i],bushData[i+1],bushData[i+2],bushData[i+3],bushData[i+4],bushData[i+5]},this->vertexDescription};
        this->vertices.push_back(v);
    }

    this->init();
}


