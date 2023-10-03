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
    //printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

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
