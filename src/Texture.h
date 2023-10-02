//
// Created by Tonz on 02.10.2023.
//
#pragma once

#include <string>
#include <vector>

#include "glm.hpp"

class Texture {
public:
    explicit Texture(const std::string& name);
    [[nodiscard]] const bool& isValid() const;

    void bind(const uint32_t& textureUnit) const;

    ~Texture();

private:
    uint32_t id;

    std::vector<std::reference_wrapper<uint8_t>> data;
    bool valid{false};
    glm::vec<2,int> dimensions{0};
    int components{0};
    std::string name{};

    uint8_t* rawData{nullptr};
};