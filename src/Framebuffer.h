//
// Created by Tonz on 19.10.2023.
//

#pragma once

#include <cstdint>
#include <memory>
#include "Texture.h"

class Framebuffer {
public:
    Framebuffer();
    void bind() const;
    void unbind() const;
    [[nodiscard]] const uint32_t& getTargetId() const;

    ~Framebuffer();

private:
    uint32_t id{0};
    uint32_t rboId{0};

    std::unique_ptr<Texture> target;

};