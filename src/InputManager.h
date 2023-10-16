//
// Created by Tonz on 02.10.2023.
//

#pragma once

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cctype>
#include <functional>
#include <unordered_map>
#include <vector>
#include "vec2.hpp"
#include "Observer.h"

struct InputMap{
    inline void addPairing(const char key, std::function<void(int key)> response){
        map[std::toupper(key)].push_back(response);
    }
    inline void addPairing(std::vector<char>&& keys, std::function<void(int key)> response){
        for (const char &key : keys){
            map[std::toupper(key)].push_back(response);
        }
    }

    std::unordered_map<int,std::vector<std::function<void(int key)>>> map{};
};

class InputManager : public Subject<uint32_t,uint32_t> {
public:
    static inline InputManager& getInstance(){
        if(instance == nullptr)
            instance = new InputManager();
        return *instance;
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorCallback(GLFWwindow *window, double x, double y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    InputMap& getInputMap();

    void registerMouseCallback(std::function<void(double, double, double, double)> f);

private:
    InputManager() = default;

    inline static InputManager* instance{nullptr};

    InputMap inputMap{};

    glm::vec2 cursorPos;

    std::vector<std::function<void(double, double, double, double)>> mouseCallbacks{};

    void keyCallbackInternal(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursorCallbackInternal(GLFWwindow *window, double x, double y);
    void mouseButtonCallbackInternal(GLFWwindow* window, int button, int action, int mode);
};