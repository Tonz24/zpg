//
// Created by Tonz on 10.10.2023.
//
#pragma once
#include "Renderable.h"
#include "LightMaterial.h"

class Light : public Renderable {
public:
    explicit Light(const glm::vec3& color = {0,1,0},TransformationComposite* transformation = new TransformationComposite(), Model* model = new Cube());

    void setColor(const glm::vec3& color);
    void setAttenuation(const glm::vec3& attenuation);

    ~Light() override;

private:

    inline static int lightCount{0};
    inline static int assignPosition(){
        return lightCount++;
    }
    inline static void releasePosition(){
        lightCount--;
    }
    static void reassignPositions(const int& from);
    static void uploadLightCount();

    inline static std::vector<Light*> lights{};

    int uboPosition{0};
    void uploadToGpu();

    glm::vec3 color{1,1,1};
    glm::vec3 attenuation{1.0f,0.09f,0.032f};
};