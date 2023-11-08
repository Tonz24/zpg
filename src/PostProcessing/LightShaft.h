//
// Created by Tonz on 08.11.2023.
//

#pragma once


#include "ImageEffect.h"
#include "PostFX.h"
#include "../Lights/PointLight.h"

class LightShaft : public ImageEffect {
public:

    LightShaft(){
        this->add.setTex1(PostFX::getInstance().occlusionMap->getTarget());
        this->add.setTex2(PostFX::getInstance().getPing().getTarget());
    }

    void apply() override {
        radialBlur.centers.clear();
        for (const auto &item : Application::getInstance().getScene().getRayCasters()){
            glm::mat4 viewMat = Application::getInstance().getScene().getActiveCamera().getViewMatrix();
            glm::mat4 projMat = Application::getInstance().getScene().getActiveCamera().getProjMatrix();
            glm::vec4 clipPos = projMat * viewMat * item->getModelMat() * glm::vec4{0,0,0,1};
            glm::vec4 ndcPos = clipPos / clipPos.w;
            glm::vec4 screenSpacePos = ndcPos * 0.5f + 0.5f;
            //if ((screenSpacePos.x >= 0.0 && screenSpacePos.x <= 1.0) && (screenSpacePos.y >= 0.0 && screenSpacePos.y <= 1.0))
                radialBlur.centers.push_back(glm::vec2{screenSpacePos.x,screenSpacePos.y});
        }
        this->radialBlur.apply();
        this->add.apply();
    }

private:
    class RadialBlur : public ImageEffect {
    public:
        explicit RadialBlur(int sampleCount) : ImageEffect("effect_radial_blur"), sampleCount(sampleCount){}
        [[nodiscard]] const ShaderProgram& getShader() const {
            return *this->shader;
        }

        void apply() override {
            if (this->shader != nullptr) {
                //glDisable(GL_BLEND);
                PostFX& instance = PostFX::getInstance();
                instance.bindPong();

                this->shader->bind();
                this->uploadValues();

                instance.drawToTargetFromOcclusionFBO();
                instance.swapValues();
            }
        }

    protected:
        void uploadValues() override {
            ImageEffect::uploadValues();
            this->shader->setVar("sampleCount",this->sampleCount);
            this->shader->setVar("rcpSampleCount", 1.0f / static_cast<float>(this->sampleCount));

            this->shader->setVar("decay",this->decay);
            this->shader->setVar("weight",this->weight);
            this->shader->setVar("density",this->density);
            this->shader->setVar("exposure",this->exposure);

            this->shader->setVar("rcpCenterCount", 1.0f / static_cast<float>(this->centers.size()));
            this->shader->setVar("centerCount",static_cast<int>(this->centers.size()));
            for (int i = 0; i < this->centers.size(); ++i) {
                this->shader->setVar("centers[" + std::to_string(i) + "]",this->centers[i]);
            }
        }

    public:
        int sampleCount{10};
        float decay{1.0};
        float weight{1.0};
        float density{1.0};
        float exposure{1.0};
        std::vector<glm::vec2> centers{};
    };

    class Add : public ImageEffect{
    public:
        Add() : ImageEffect("effect_add"){}

        void setTex1(const Texture* tex){
            this->tex1 = tex;
        }

        void setTex2(const Texture* tex){
            this->tex2 = tex;
        }

    protected:
        void uploadValues() override {
            ImageEffect::uploadValues();
            this->tex1->bind(0);
            this->tex2->bind(1);
        }

    private:
        const Texture* tex1;
        const Texture* tex2;
    };

    RadialBlur radialBlur{256};
    Add add;
};


