//
// Created by Tonz on 21.10.2023.
//

#pragma once


#include "ImageEffect.h"

class BloomEffect : public ImageEffect {
public:
    BloomEffect(int sampleCount = 6);

    void apply() override;

protected:
    void uploadValues() override;

private:
    class DownSample : public ImageEffect {

    public:

        void apply() override;
        explicit DownSample(int sampleFrom, int sampleTo);
        const ShaderProgram& getShader() const {
            return *this->shader;
        }

    protected:
        void uploadValues() override;

    private:
        int sampleFrom{0}, sampleTo{0};
    };
    class UpSample : public ImageEffect {

    public:
        void apply() override;
        explicit UpSample(int sampleFrom, int sampleTo) : ImageEffect("effect_upsample"), sampleFrom(sampleFrom), sampleTo(sampleTo) {}
        const ShaderProgram& getShader() const {
            return *this->shader;
        }

    protected:
        void uploadValues() override;

    private:
        int sampleFrom{0}, sampleTo{0};
    };

    int sampleCount{6};
    std::vector<DownSample> downSamples{};
    std::vector<UpSample> upSamples{};
};
