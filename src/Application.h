//
// Created by Tonz on 26.09.2023.
//

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "UBO.h"
#include "Scene.h"
#include "Window.h"
#include "Framebuffer.h"
#include "PostProcessing/ImageEffect.h"

class Application {
public:
    inline static Application& getInstance() {
        if(appInstance == nullptr)
            appInstance = new Application();
        return *appInstance;
    }

    [[nodiscard]] const UBO& getTransformBuffer() const;
    [[nodiscard]] const UBO& getLightBuffer() const;

    void initialize();
    void run();
    void terminate();

    Scene& getScene(){
        return *this->scene;
    }

    void setScene(std::unique_ptr<Scene>& scene);

    [[nodiscard]] const Window& getWindow() const;
    [[nodiscard]] Window& getWindow();

    float getTime();
    float getDeltaTime();
    void setUsePostFX(bool value);

    bool getUsePostFx() const;

    const void bindShadowMapShader();


private:
    Application();
    Application(Application& app) = delete;
    void operator = (Application& app) = delete;
    inline static Application* appInstance{nullptr};

    std::unique_ptr<Scene> scene{nullptr};
    std::unique_ptr<UBO> transformBuffer;
    std::unique_ptr<UBO> lightBuffer;
    std::unique_ptr<Window> window;

    bool initialized{false};

    float currentTime{0};
    float deltaTime{0};
    float lastTime{0};
    bool usePostFX{true};

    const ShaderProgram* shadowMapShader;
};