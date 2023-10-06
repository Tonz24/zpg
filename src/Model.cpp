//
// Created by Tonz on 26.09.2023.
//

#include "Model.h"

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
    /*glEnableVertexAttribArray(0); //enable vertex position
    glEnableVertexAttribArray(1); //enable vertex color

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(3*sizeof(float)));*/

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

Model::Model(const VertexType& type) : type(type){
    for(int i = 0; i < 17424; i+= 6){
        Vertex v({suziSmooth[i],suziSmooth[i+1],suziSmooth[i+2]},{1,1,1},{suziSmooth[i+3],suziSmooth[i+4],suziSmooth[i+5]},{1,1});
        this->vertices.push_back(v);
    }
    this->init();
}