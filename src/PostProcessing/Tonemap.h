//
// Created by Tonz on 19.10.2023.
//

#pragma once


#include "ImageEffect.h"

class Tonemap : public ImageEffect{
protected:
    Tonemap() : ImageEffect("effect_tonemap"){}
};


class TonemapACES : public Tonemap{
public:
    TonemapACES() : Tonemap(){}

protected:
    void uploadValues() override {
        ImageEffect::uploadValues();
        this->shader->setVar("tonemapType", 0);
    }
};


class TonemapFilmic : public Tonemap{
public:
    TonemapFilmic() : Tonemap(){}

protected:
    void uploadValues() override {
        ImageEffect::uploadValues();
        this->shader->setVar("tonemapType", 1);
    }
};

class TonemapReinhard : public Tonemap{
public:
    TonemapReinhard() : Tonemap(){}

protected:
    void uploadValues() override {
        ImageEffect::uploadValues();
        this->shader->setVar("tonemapType", 2);
    }
};

