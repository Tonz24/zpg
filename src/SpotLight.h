//
// Created by Tonz on 17.10.2023.
//

#pragma once


#include "Light.h"

class SpotLight : public Light {
public:
    explicit SpotLight(const glm::vec3& color = {0,1,0},TransformationComposite* transformation = new TransformationComposite(), Model* model = new Cube());

    ~SpotLight() override;

    void setCutoffAngle(float cutoffAngle);

    void setDirection(const glm::vec3 &direction);

    void setPosition(const glm::vec3 &position);

private:
    glm::vec3 position{0,0,0};
    glm::vec3 direction{1,0,0};
    float cutoffAngle{35.0f};

    inline static int lightCount{0};
    inline static int assignPosition(){
        return lightCount++;
    }
    inline static void releasePosition(){
        lightCount--;
    }

    void uploadToGpu() override;

    static void reassignPositions(const int& from);
    static void uploadLightCount();

    inline static std::vector<SpotLight*> lights{};

    static inline constexpr size_t spotLightOffset = sizeof(glm::vec4)*3*MAX_N_POINT_LIGHTS + sizeof(glm::vec4)*4*MAX_N_SPOT_LIGHTS + sizeof(int);
};


