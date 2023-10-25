//
// Created by Tonz on 17.10.2023.
//

#pragma once


class IDrawable {
public:
    virtual void draw() = 0;
    virtual void drawForShadowMapping() = 0;
    virtual const ConstantMaterial& getMaterial() const = 0;
};


