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

    [[nodiscard]] const Window& getWindow() const;
    [[nodiscard]] Window& getWindow();

    float getTime();
    float getDeltaTime();

private:
    Application();
    Application(Application& app) = delete;
    void operator = (Application& app) = delete;
    inline static Application* appInstance{nullptr};

    std::unique_ptr<Scene> scene{nullptr};
    std::unique_ptr<UBO> transformBuffer;
    std::unique_ptr<UBO> lightBuffer;
    std::unique_ptr<Window> window;

    uint32_t fboId{0};
    uint32_t fboTexId{0};
    uint32_t rboId{0};
    const Shader* fboShader;
    const Shader* displayShader;

    uint32_t quadVBO{0};
    uint32_t quadVAO{0};

   Framebuffer* framebuffer[2];

    bool initialized{false};

    float currentTime{0};
    float deltaTime{0};
    float lastTime{0};

     float quadVertices[24] = {
         -1.0f,  1.0f,       0.0f, 1.0f,
         -1.0f, -1.0f,       0.0f, 0.0f,
         1.0f, -1.0f,        1.0f, 0.0f,

         -1.0f,  1.0f,       0.0f, 1.0f,
         1.0f, -1.0f,        1.0f, 0.0f,
         1.0f,  1.0f,        1.0f, 1.0f
    };
};