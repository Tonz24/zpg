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

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string &name, const std::vector<std::string>& names) :id(0) {
    stbi_set_flip_vertically_on_load(false);
    std::string fullName{R"(..\Assets\Textures\)" + name};

    glm::vec<2,int> size{0};
    int comp{0};

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);

    for (unsigned int i = 0; i < names.size(); i++){
        std::string actualName = fullName + "\\" + names[i];
        uint8_t* texData = stbi_load(actualName.c_str(),&size.x,&size.y,&comp,0);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        stbi_image_free(texData);
    }
    this->dimensions = size;
    this->valid = true;
    this->name = name;
    this->components = comp;

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const glm::vec<2,int>& dimensions) : dimensions(dimensions), id(0), components(3) {

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glm::vec3 borderColor = {0,0,0};

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &borderColor[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, NULL);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->valid = true;
}

Texture::Texture(const glm::vec<2,glm::i32,glm::packed_highp> &dimensions, int h):  dimensions(dimensions), id(0), components(3) {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, dimensions.x, dimensions.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->valid = true;
}


const bool &Texture::isValid() const {
    return this->valid;
}

void Texture::bind(const uint32_t &textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, this->id);
}

Texture::~Texture() {
    if (this->rawData != nullptr)
        stbi_image_free(this->rawData);
    glDeleteTextures(1,&this->id);
}

const uint32_t &Texture::getId() const {
    return this->id;
}

const glm::vec<2, int> &Texture::getDimensions() const {
    return dimensions;
}

void Texture::bindCubemap(const uint32_t &textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
}

const uint8_t * Texture::getData() const {
    return this->rawData;
}

Texture::Texture(const glm::vec2 &dimensions, float h, float g) : dimensions(dimensions), id(0), components(2) {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, dimensions.x, dimensions.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->valid = true;
}
