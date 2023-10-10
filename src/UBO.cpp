//
// Created by Tonz on 09.10.2023.
//
#include "UBO.h"

UBO::UBO(const size_t & size, const uint32_t& bindPoint, const void* data) : id(0), bindPoint(bindPoint), size(size) {
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_UNIFORM_BUFFER, this->id);
    glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
}

void UBO::setData(const uint32_t &offset, const uint32_t& size, const void *data) const {
    glBindBuffer(GL_UNIFORM_BUFFER, this->id);
    glBindBufferBase(GL_UNIFORM_BUFFER, this->bindPoint, this->id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UBO::setData(const uint32_t &size, const void *data) const {
    glBindBuffer(GL_UNIFORM_BUFFER, this->id);
    glBindBufferBase(GL_UNIFORM_BUFFER, this->bindPoint, this->id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
}

UBO::~UBO() {
    glDeleteBuffers(1,&this->id);
}