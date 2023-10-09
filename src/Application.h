//
// Created by Tonz on 26.09.2023.
//

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "UBO.h"
#include "Scene.h"

class Application {
public:
    inline static Application& getInstance() {
        if(appInstance == nullptr)
            appInstance = new Application();
        return *appInstance;
    }

    GLFWwindow* getWindow(){
        return this->window;
    }

    const UBO& getTransformBuffer() const;

    void initialize();
    void run();
    void terminate();

    Scene& getScene(){
        return *this->scene;
    }

    float getTime();
    float getDeltaTime();

private:
    inline static Application* appInstance{nullptr};

    std::unique_ptr<Scene> scene{nullptr};
    std::unique_ptr<UBO> transformBuffer;

    Application();

    GLFWwindow* window{nullptr};

    bool initialized{false};

    float currentTime{0};
    float deltaTime{0};
    float lastTime{0};
};