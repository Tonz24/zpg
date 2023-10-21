//
// Created by Tonz on 21.10.2023.
//

#include "BloomEffect.h"
#include "PostFX.h"

void BloomEffect::DownSample::apply() {
    if (this->shader != nullptr) {
        PostFX& instance = PostFX::getInstance();
        instance.bindPong(this->sampleTo);

        this->uploadValues();
        auto dims = instance.getPong().getTargetDimensions(this->sampleTo);

        glViewport(0, 0, dims.x, dims.y);
        instance.drawToTarget(this->sampleFrom);
        instance.swapValues();
    }
}

BloomEffect::DownSample::DownSample(int sampleFrom, int sampleTo) : ImageEffect("effect_downsample"), sampleFrom(sampleFrom), sampleTo(sampleTo) {
}

void BloomEffect::DownSample::uploadValues() {
    ImageEffect::uploadValues();
    this->shader->setVec2f("srcResolution",PostFX::getInstance().getPing().getTargetDimensions(this->sampleFrom));
    this->shader->setInt("doPrefilter",this->sampleFrom == 0);
    this->shader->setFloat("bloomTreshold",1.0f);
}

void BloomEffect::UpSample::apply() {
    if (this->shader != nullptr) {
        PostFX& instance = PostFX::getInstance();
        instance.bindPong(this->sampleTo);

        this->uploadValues();
        auto dims = instance.getPong().getTargetDimensions(this->sampleTo);

        glViewport(0, 0, dims.x, dims.y);
        instance.drawToTarget(this->sampleFrom);
        instance.swapValues();
    }
}

void BloomEffect::UpSample::uploadValues() {
    ImageEffect::uploadValues();
    this->shader->setFloat("filterRadius",0.005f);
}

void BloomEffect::apply() {
    this->downSamples[0].getShader().use();
    for (auto &item : this->downSamples){
        item.apply();
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_FUNC_ADD);
    this->upSamples[0].getShader().use();
    for (auto &item : this->upSamples){
        item.apply();
    }
    glDisable(GL_BLEND);
}

void BloomEffect::uploadValues() {
    ImageEffect::uploadValues();
}

BloomEffect::BloomEffect(int sampleCount) : ImageEffect(), sampleCount(sampleCount) {
    for (int i = 0; i < sampleCount; ++i) {
        downSamples.push_back(DownSample(i,i+1));
        upSamples.push_back(UpSample( sampleCount - i,sampleCount - i - 1));
    }
}
