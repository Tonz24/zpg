//
// Created by Tonz on 26.09.2023.
//

#include "Model.h"

#include <utility>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include <iostream>

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
}

Model::Model() {
    std::vector<VertexElement*> desc{};
    desc.push_back(new PosElement());
    desc.push_back(new NorElement());
    this->vertexDescription = std::move(desc);
}

Model::Model(const std::string &path) {
    std::string fullPath = R"(..\Assets\Models\)" + path;
    Assimp::Importer importer;
    unsigned int importOptions =   aiProcess_OptimizeMeshes              // sloučení malých plošek
                                 | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
                                 | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
                                 | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

    const aiScene* scene = importer.ReadFile(fullPath,importOptions);

    if (scene){
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        aiMesh* mesh = scene->mMeshes[0];

        for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
            Vertex v1;
            Vertex v2;
            Vertex v3;
            aiFace f = mesh->mFaces[i];

            if(mesh->HasPositions()) {
                v1.pos = {mesh->mVertices[f.mIndices[0]].x, mesh->mVertices[f.mIndices[0]].y, mesh->mVertices[f.mIndices[0]].z};
                v2.pos = {mesh->mVertices[f.mIndices[1]].x, mesh->mVertices[f.mIndices[1]].y, mesh->mVertices[f.mIndices[1]].z};
                v3.pos = {mesh->mVertices[f.mIndices[2]].x, mesh->mVertices[f.mIndices[2]].y, mesh->mVertices[f.mIndices[2]].z};
            }

            if(mesh->HasNormals())
                v1.normal = {mesh->mNormals[f.mIndices[0]].x, mesh->mNormals[f.mIndices[0]].y, mesh->mNormals[f.mIndices[0]].z};
                v2.normal = {mesh->mNormals[f.mIndices[1]].x, mesh->mNormals[f.mIndices[1]].y, mesh->mNormals[f.mIndices[1]].z};
                v3.normal = {mesh->mNormals[f.mIndices[2]].x, mesh->mNormals[f.mIndices[2]].y, mesh->mNormals[f.mIndices[2]].z};

            if(mesh->HasTextureCoords(0)) {
                v1.uv = {mesh->mTextureCoords[0][f.mIndices[0]].x, mesh->mTextureCoords[0][f.mIndices[0]].y};
                v2.uv = {mesh->mTextureCoords[0][f.mIndices[1]].x, mesh->mTextureCoords[0][f.mIndices[1]].y};
                v3.uv = {mesh->mTextureCoords[0][f.mIndices[2]].x, mesh->mTextureCoords[0][f.mIndices[2]].y};
            }
            this->vertices.push_back(v1);
            this->vertices.push_back(v2);
            this->vertices.push_back(v3);
        }
        this->init();
    }
    else
        std::cerr << "object: " + path << " not found!" << std::endl;
}