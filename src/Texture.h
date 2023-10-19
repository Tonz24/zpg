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
    explicit Texture(const glm::vec<2,int>& dimensions);
    ~Texture();


    void bind(const uint32_t& textureUnit) const;

    [[nodiscard]] const bool& isValid() const;
    [[nodiscard]] const uint32_t& getId() const;

private:
    uint32_t id;

    std::vector<std::reference_wrapper<uint8_t>> data;
    bool valid{false};
    glm::vec<2,int> dimensions{0};
    int components{0};
    std::string name{};

    uint8_t* rawData{nullptr};
};