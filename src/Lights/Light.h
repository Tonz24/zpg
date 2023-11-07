//
// Created by Tonz on 10.10.2023.
//
#pragma once
#include "../SceneObject.h"
#include "../Materials/ConstantMaterial.h"
#include "../Framebuffer.h"

class Light : public SceneObject {
public:
    explicit Light(const glm::vec3& color = {0,1,0}, Model* model = nullptr);

    void setColor(const glm::vec3& color);
    void setAttenuation(const glm::vec3& attenuation);

    void draw() override;
    void tick() override;

    virtual ~Light() = default;

    virtual void setTranslation(const glm::vec3 &translation) override;
    virtual void translate(const glm::vec3 &translation) override;
    virtual void setRotation(const float &angle, const glm::vec3 &axis) override;
    virtual void rotate(const float &angle) override;
    virtual void setScale(const glm::vec3 &scale) override;
    virtual glm::mat4 getViewMat() const = 0;
    virtual void uploadLightSpaceMatrices() const = 0;
    virtual glm::mat4 getLightSpaceMatrix() const = 0;

    [[nodiscard]] const Framebuffer& getShadowFbo() const;

    void activate();
    void deactivate();

protected:

    int uboPosition{0};
    virtual void uploadToGpu() = 0;
    virtual void reassignPositionsImpl(const int& from) = 0;
    virtual void uploadLightCountImpl() = 0;
    virtual int assignPositionImpl() = 0;
    virtual void releasePositionImpl() = 0;
    virtual void pushToVector() = 0;

    glm::vec3 color{1,1,1};
    glm::vec3 attenuation{1.0f,0.09f,0.032f};

    static inline constexpr int MAX_N_POINT_LIGHTS = 30;
    static inline constexpr int MAX_N_SPOT_LIGHTS = 30;
    static inline constexpr int MAX_N_DIRECTIONAL_LIGHTS = 30;

    bool active{false};

    std::unique_ptr<Framebuffer> shadowFBO;

    glm::mat4 projMat;
    glm::mat4 viewMat;
};