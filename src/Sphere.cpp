//
// Created by Tonz on 07.10.2023.
//

#include "Sphere.h"


Sphere::Sphere() : Model() {
    for(int i = 0; i < sphere.size(); i+= 6){
        Vertex v{{sphere[i],sphere[i+1],sphere[i+2],sphere[i+3],sphere[i+4],sphere[i+5]},this->vertexDescription};
        this->vertices.push_back(v);
    }
    this->init();
}