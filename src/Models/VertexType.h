//
// Created by Tonz on 07.10.2023.
//

#pragma once

#include <cstdint>
class VertexElement{
public:
    virtual int getElementOffset() const = 0;
    virtual int getElementCount() const = 0;
};

class PosElement : public VertexElement{
public:
    virtual int getElementOffset() const override {return 0;}
    virtual int getElementCount() const override {return 3;}
};

class NorElement : public PosElement{
public:
    virtual int getElementOffset() const override {return 3;}
};

class ColElement : public PosElement{
public:
    virtual int getElementOffset() const override {return 6;}
};

class UvElement : public VertexElement{
public:
    virtual int getElementOffset() const override {return 9;}
    virtual int getElementCount() const override {return 2;}
};