//
// Created by Tonz on 02.10.2023.
//
#pragma once

#include <string>
#include <vector>

#include "glm.hpp"

class Texture {
public:

    //Load from path
    explicit Texture(const std::string& name);

    //cubemap constructor
    explicit Texture(const std::string& name,const std::vector<std::string>& names);

    //constructor for texture with specified dimensions with no data
    explicit Texture(const glm::vec<2,int>& dimensions);

    //don't use
    explicit Texture(const glm::vec<2,glm::i32,glm::packed_highp>& dimensions, int h);
    ~Texture();

    void bind(const uint32_t& textureUnit) const;
    void bindCubemap(const uint32_t& textureUnit) const;


    [[nodiscard]] const bool& isValid() const;
    [[nodiscard]] const uint32_t& getId() const;

    [[nodiscard]] const glm::vec<2, int> &getDimensions() const;

    [[nodiscard]] const uint8_t * getData() const;

private:
    uint32_t id;

    std::vector<std::reference_wrapper<uint8_t>> data;
    bool valid{false};
    glm::vec<2,int> dimensions{0};
    int components{0};
    std::string name{};

    uint8_t* rawData{nullptr};
};