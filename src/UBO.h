//
// Created by Tonz on 09.10.2023.
//

#pragma once
#include <cstdint>
#include <GL/glew.h>

class UBO {
public:
    UBO(const size_t & size, const uint32_t& bindPoint, const void* data = nullptr);

    void setData(const uint32_t& offset,const uint32_t& size, const void* data) const;
    void setData(const uint32_t& size, const void* data) const;

    ~UBO();

private:
    uint32_t id;
    uint32_t bindPoint;
    size_t size;
};