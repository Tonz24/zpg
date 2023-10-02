//
// Created by Tonz on 02.10.2023.
//
#include <GL/glew.h>
#include <iostream>
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& name) : id(0) {

    std::string fullName{R"(..\Assets\Textures\)" + name};

    glm::vec<2,int> size{0};
    int comp{0};

    if( stbi_info(fullName.c_str(),&size.x,&size.y,&comp) == 0) {
        std::cerr << "File \"" << fullName << "\\\" not found." << std::endl;
        return;
    }
    stbi_set_flip_vertically_on_load(true);
    this->rawData = stbi_load(fullName.c_str(),&size.x,&size.y,&comp,4);

    this->data = std::vector<std::reference_wrapper<uint8_t>>(rawData, rawData + (size.x * size.y * 3));
    this->dimensions = size;
    this->valid = true;
    this->name = name;
    this->components = comp;

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->dimensions.x, this->dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &this->data.data()->get());
    glGenerateMipmap(GL_TEXTURE_2D);
}

const bool &Texture::isValid() const {
    return this->valid;
}

void Texture::bind(const uint32_t &textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, this->id);
}

Texture::~Texture() {
    stbi_image_free(this->rawData);
    glDeleteTextures(1,&this->id);
}