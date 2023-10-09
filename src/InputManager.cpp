//
// Created by Tonz on 02.10.2023.
//

#include "InputManager.h"

void InputManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    getInstance().keyCallbackInternal(window,key,scancode,action,mods);
}

void InputManager::keyCallbackInternal(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    for (const auto &item : this->inputMap.map[key]){
        item(key);
    }
}

void InputManager::cursorCallback(GLFWwindow *window, double x, double y) {
    getInstance().cursorCallbackInternal(window,x,y);
}

void InputManager::cursorCallbackInternal(GLFWwindow *window, double x, double y) {
    printf("cursor_callback \n");
}

void InputManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) {
    getInstance().mouseButtonCallbackInternal(window,button,action,mode);
}

void InputManager::mouseButtonCallbackInternal(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS)
        printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

InputMap &InputManager::getInputMap() {
    return this->inputMap;
}

void InputManager::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    glm::vec2 oldPos = InputManager::getInstance().cursorPos;
    glm::vec2 delta = {xpos - oldPos.x, ypos - oldPos.y};

    for (const auto& func : InputManager::getInstance().mouseCallbacks){
        func(xpos,ypos,delta.x,delta.y);
    }

    InputManager::getInstance().cursorPos = {xpos,ypos};
}

void InputManager::registerMouseCallback(std::function<void(double, double, double, double)> f) {
    this->mouseCallbacks.push_back(f);
}