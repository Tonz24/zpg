//
// Created by Tonz on 05.11.2023.
//

#pragma once


#include "Light.h"

class DirectionalLight : public Light{
public:
    explicit DirectionalLight(const glm::vec3& color = {0,1,0},const glm::vec3& direction = {0,1,0}, Model* model = new Cube());

    ~DirectionalLight() override;

    glm::mat4 getViewMat() const override;

    void uploadLightSpaceMatrices() const override;

    glm::mat4 getLightSpaceMatrix() const override;

    void setDirection(const glm::vec3 &direction);

    const Material &getMaterial() const override;

private:
    inline static int lightCount{0};
    inline static int assignPosition(){
        return lightCount++;
    }
    inline static void releasePosition(){
        lightCount--;
    }

    void uploadToGpu() override;

protected:
    void reassignPositionsImpl(const int &from) override;
    void uploadLightCountImpl() override;
    int assignPositionImpl() override;

    void releasePositionImpl() override;

    void pushToVector() override;

private:
    glm::vec3 direction{0,1,0};

    static void reassignPositions(const int& from);
    static void uploadLightCount();

    inline static std::vector<DirectionalLight*> lights{};

    static inline constexpr size_t directionalLightOffset = sizeof(glm::vec4)*3*MAX_N_POINT_LIGHTS + sizeof(glm::vec4)*4*MAX_N_SPOT_LIGHTS + sizeof(glm::vec4)*3*MAX_N_DIRECTIONAL_LIGHTS + sizeof(int)*2;
};



