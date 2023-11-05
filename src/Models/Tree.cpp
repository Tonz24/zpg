//
// Created by Tonz on 26.10.2023.
//

#include "Tree.h"

void Tree::fillVector() {
    treeData.insert(treeData.end(), &tree[0], &tree[556884 - 1]);
    vectorFilled = true;
}

Tree::Tree() {
    if (!vectorFilled) fillVector();

    for(int i = 0; i < 556884 - 6; i+= 6){
        Vertex v{{treeData[i],treeData[i+1],treeData[i+2],treeData[i+3],treeData[i+4],treeData[i+5]},this->vertexDescription};
        this->vertices.push_back(v);
    }

    this->init();
}
