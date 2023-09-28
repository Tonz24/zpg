//
// Created by Tonz on 26.09.2023.
//

#include "Model.h"

Model::Model(std::vector<Vertex>& vertices, Material& material) : material(material), vertices(vertices) {
    init();
}

Model::Model(std::vector<Vertex> &vertices, Material& material, glm::vec3 &translation) : Model(vertices,material) {
    this->translation = translation;
}

Model::~Model() {
    glDeleteVertexArrays(1,&this->vao);
    glDeleteBuffers(1,&this->vbo);
}

void Model::draw() {
    this->material.uploadTranslation(this->translation);
    this->material.uploadVariables();
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}

void Model::init() {
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

    //init model VAO
    glGenVertexArrays(1, &this->vao); //generate the VAO
    glBindVertexArray(this->vao); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //enable vertex attributes
    glEnableVertexAttribArray(2); //enable vertex attributes

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),  (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6*sizeof(float)));
}


