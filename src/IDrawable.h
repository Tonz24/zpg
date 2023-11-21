//
// Created by Tonz on 17.10.2023.
//

#pragma once

#include "Materials/Material.h"

class IDrawable {
public:

    explicit IDrawable() : stencilId(++stencilIdCounter){}

    virtual void draw() = 0;
    virtual void drawForShadowMapping() = 0;
    virtual const Material& getMaterial() const = 0;
    virtual const bool& canCastRays() const = 0;
    virtual void setCanCastRays(bool value) = 0;
    virtual const glm::mat4& getModelMat() const = 0;

    [[nodiscard]] const uint32_t& getStencilId(){
        return this->stencilId;
    }

private:
    const uint32_t stencilId{0};
    inline static uint32_t stencilIdCounter{0};
};
