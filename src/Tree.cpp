//
// Created by Tonz on 17.10.2023.
//

#include "Tree.h"

Tree::Tree() : Model() {
    for(int i = 0; i < tree.size(); i+= 6){
        Vertex v{{tree[i],tree[i+1],tree[i+2],tree[i+3],tree[i+4],tree[i+5]},this->vertexDescription};
        this->vertices.push_back(v);
    }
    this->init();
}