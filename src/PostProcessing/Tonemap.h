//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "ImageEffect.h"

class Tonemap : public ImageEffect{
public:
    virtual void apply() override {
        ImageEffect::apply();
    }

protected:
    Tonemap() : ImageEffect("effect_tonemap"){}
};


class TonemapACES : public Tonemap{
public:
    TonemapACES() : Tonemap(){}

    void apply() override{
        Tonemap::apply();
        this->shader->setInt("tonemapType",0);
    }
};


class TonemapFilmic : public Tonemap{
public:
    TonemapFilmic() : Tonemap(){}

    void apply() override{
        Tonemap::apply();
        this->shader->setInt("tonemapType",1);
    }
};

class TonemapReinhard : public Tonemap{
public:
    TonemapReinhard() : Tonemap(){}

    void apply() override{
        Tonemap::apply();
        this->shader->setInt("tonemapType",2);
    }
};

