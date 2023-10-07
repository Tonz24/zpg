//
// Created by Tonz on 26.09.2023.
//

#include "Model.h"

#include <utility>

Model::~Model() {
    glDeleteVertexArrays(1,&this->vao);
    glDeleteBuffers(1,&this->vbo);
}

void Model::draw() {
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}

void Model::init() {
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->vao); //generate the VAO
    glBindVertexArray(this->vao); //bind the VAO

    int pointersUsed{0}, offsets{0};

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glEnableVertexAttribArray(pointersUsed);
    glVertexAttribPointer(pointersUsed, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsets*sizeof(float)));
    pointersUsed++;
    offsets += 3;
    glEnableVertexAttribArray(pointersUsed);
    glVertexAttribPointer(pointersUsed, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsets*sizeof(float)));
    pointersUsed++;
    offsets += 3;
    glEnableVertexAttribArray(pointersUsed);
    glVertexAttribPointer(pointersUsed, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsets*sizeof(float)));
    pointersUsed++;
    offsets += 3;
    glEnableVertexAttribArray(pointersUsed);
    glVertexAttribPointer(pointersUsed, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsets*sizeof(float)));
    pointersUsed++;
    offsets += 2;
}

Model::Model(std::vector<VertexElement*> types) : vertexDescription(std::move(types)){
    for(int i = 0; i < 17280; i+= 6){
        Vertex v{{sphere[i],sphere[i+1],sphere[i+2],sphere[i+3],sphere[i+4],sphere[i+5]},this->vertexDescription};
        this->vertices.push_back(v);
    }
    this->init();
}