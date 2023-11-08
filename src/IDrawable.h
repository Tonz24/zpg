//
// Created by Tonz on 17.10.2023.
//

#pragma once


class IDrawable {
public:
    virtual void draw() = 0;
    virtual void drawForShadowMapping() = 0;
    virtual const Material& getMaterial() const = 0;
    virtual const bool& canCastRays() const = 0;
    virtual void setCanCastRays(bool value) = 0;
    virtual const glm::mat4& getModelMat() const = 0;
};