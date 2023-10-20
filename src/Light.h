//
// Created by Tonz on 10.10.2023.
//
#pragma once
#include "Renderable.h"
#include "Materials/LightMaterial.h"

class Light : public Renderable {
public:
    explicit Light(const glm::vec3& color = {0,1,0},TransformationComposite* transformation = new TransformationComposite(), Model* model = new Cube());

    void setColor(const glm::vec3& color);
    void setAttenuation(const glm::vec3& attenuation);

    void draw() override;
    void tick() override;

    virtual ~Light() = default;

protected:

    int uboPosition{0};
    virtual void uploadToGpu() = 0;

    glm::vec3 color{1,1,1};
    glm::vec3 attenuation{1.0f,0.09f,0.032f};

    static inline constexpr int MAX_N_POINT_LIGHTS = 30;
    static inline constexpr int MAX_N_SPOT_LIGHTS = 30;
};