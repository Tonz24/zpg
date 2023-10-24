//
// Created by Tonz on 17.10.2023.
//

#pragma once


#include "Light.h"

class SpotLight : public Light {
public:
    explicit SpotLight(const glm::vec3& color = {0,1,0}, Model* model = nullptr);

    ~SpotLight() override;

    void setOuterCutoffAngle(float cutoffAngle);
    void setInnerCutoffAngle(float cutoffAngle);

    void setDirection(const glm::vec3 &direction);

    void setPosition(const glm::vec3 &position);

    void uploadLightSpaceMatrices() const override;


protected:
    void reassignPositionsImpl(const int &from) override;
    void uploadLightCountImpl() override;
    int assignPositionImpl() override;
    void releasePositionImpl() override;
    void pushToVector() override;

private:
    glm::vec3 position{0,0,0};
    glm::vec3 direction{1,0,0};

    glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,0.01f,10.0f);

    glm::mat4 getViewMat()const override {
        return glm::lookAt(this->position, {1,0,0},{0,1,0});
    }

    float outerCutoffAngle{35.0f};
    float innerCutoffAngle{30.0f};

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


