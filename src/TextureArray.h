//
// Created by Tonz on 07.11.2023.
//

#pragma once

#include <vector>
#include "Texture.h"

class TextureArray {
public:
    TextureArray(const std::vector<Texture>& textures);

private:
    uint32_t id{0};
};