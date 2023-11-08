//
// Created by Tonz on 17.10.2023.
//

#pragma once


#include "Light.h"

class PointLight : public Light {
public:
    explicit PointLight(const glm::vec3& color = {0,1,0}, Model* model = new Cube());

    ~PointLight() override;

    glm::mat4 getViewMat() const override;

    void uploadLightSpaceMatrices() const override;

    glm::mat4 getLightSpaceMatrix() const override;


    inline static int getLightCount(){
        return lightCount;
    }
    inline static const std::vector<PointLight*>& getLights(){
        return lights;
    }


protected:
    void reassignPositionsImpl(const int &from) override;
    void uploadLightCountImpl() override;
    int assignPositionImpl() override;

    void releasePositionImpl() override;

    void pushToVector() override;

private:

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

    inline static std::vector<PointLight*> lights{};

    static inline constexpr size_t pointLightOffset = 48*MAX_N_POINT_LIGHTS + 64*MAX_N_SPOT_LIGHTS + 112*MAX_N_DIRECTIONAL_LIGHTS;
};