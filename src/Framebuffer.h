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
    explicit Framebuffer(int mipLevels = 0);
    explicit Framebuffer(float h);
    void bind(int mipLevel = 0) const;
    void bindDepth(int mipLevel = 0) const;
    void unbind() const;
    [[nodiscard]] const uint32_t& getTargetId(int mipLevel = 0) const;
    [[nodiscard]] const glm::vec<2,int>& getTargetDimensions(int mipLevel = 0) const;

    void update(int width, int height) override;

    ~Framebuffer();

private:
    int mipLevels{0};
    uint32_t id{0};
    uint32_t rboId{0};

    std::vector<std::unique_ptr<Texture>> target;
};