//
// Created by Tonz on 19.10.2023.
//

#pragma once

#include <cstdint>
#include <memory>
#include "Texture.h"
#include "Observer.h"

class Framebuffer : public Observer<int,int> {
public:
    Framebuffer();
    void bind() const;
    void unbind() const;
    [[nodiscard]] const uint32_t& getTargetId() const;


    void update(int width, int height) override;

    ~Framebuffer();

private:
    uint32_t id{0};
    uint32_t rboId{0};

    std::unique_ptr<Texture> target;

};