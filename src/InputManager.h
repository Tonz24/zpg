//
// Created by Tonz on 02.10.2023.
//

#pragma once

#include <GLFW/glfw3.h>
#include <cstdio>

class InputManager {
public:
    static inline InputManager& getInstance(){
        if(instance == nullptr)
            instance = new InputManager();
        return *instance;
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorCallback(GLFWwindow *window, double x, double y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

private:
    InputManager() = default;

    inline static InputManager* instance{nullptr};

    void keyCallbackInternal(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursorCallbackInternal(GLFWwindow *window, double x, double y);
    void mouseButtonCallbackInternal(GLFWwindow* window, int button, int action, int mode);
};