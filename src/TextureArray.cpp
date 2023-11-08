//
// Created by Tonz on 07.11.2023.
//

#include "Application.h"
#include "TextureArray.h"

TextureArray::TextureArray(const std::vector<Texture> &textures) {

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->id);

    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, textures[0].getDimensions().x, textures[0].getDimensions().y,
                   textures.size());


    glm::vec<2, int> offsets{};
    for (int i = 0; i < textures.size(); ++i) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, textures[i].getDimensions().x, textures[i].getDimensions().y,
                        textures.size(), GL_RGBA, GL_UNSIGNED_BYTE, textures[i].getData());
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

}