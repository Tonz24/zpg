//
// Created by Tonz on 26.09.2023.
//

#pragma once
#include <GL/glew.h>
#include "Scene.h"

#include <memory>

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

    Application();

    GLFWwindow* window{nullptr};

    std::unique_ptr<Scene> scene{nullptr};

    bool initialized{false};

    float currentTime{0};
    float deltaTime{0};
    float lastTime{0};
};