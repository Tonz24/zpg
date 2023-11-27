//
// Created by Tonz on 09.10.2023.
//

#include <cstdlib>
#include "Window.h"
#include "InputManager.h"

float Window::getAspectRatio() const {
    return static_cast<float>(this->width) / static_cast<float>(this->height);
}

Window::Window(const uint32_t &width, const uint32_t &height, const std::string& name) : width(width), height(height), name(name) {
    this->glfwWindow = glfwCreateWindow(1920, 1080, this->name.c_str(), glfwGetPrimaryMonitor(), NULL);
    if (!this->glfwWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->glfwWindow);
    glfwSwapInterval(0);

    glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int fbWidth{0},fbHeight{0};
    glfwGetFramebufferSize(this->glfwWindow,&fbWidth,&fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glfwSetKeyCallback(this->glfwWindow,&InputManager::keyCallback);
    glfwSetCursorPosCallback(this->glfwWindow, &InputManager::cursorCallback);
    glfwSetMouseButtonCallback(this->glfwWindow, &InputManager::mouseButtonCallback);
    glfwSetCursorPosCallback(this->glfwWindow, &InputManager::cursorPositionCallback);
    glfwSetWindowSizeCallback(this->glfwWindow, Window::window_size_callback);

    /*std::function<void(int)> f = [this](int key){
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        int wWidth = mode->width;
        int wHeight = mode->height;

        this->fullscreen = !this->fullscreen;
        glfwMakeContextCurrent(this->glfwWindow);
        if (this->fullscreen){
            glfwSetWindowMonitor(this->glfwWindow,glfwGetPrimaryMonitor(),0 ,0 ,wWidth, wHeight, GLFW_DONT_CARE);
        }
        else{
            glfwSetWindowMonitor(this->glfwWindow,NULL,100 ,100 ,this->width,this->height, GLFW_DONT_CARE);
        }
    };
    InputManager::getInstance().getInputMap().addPairing('f',f);
    std::function<void(int)> v = [this](int key){
        this->vsync = !this->vsync;
        glfwMakeContextCurrent(this->glfwWindow);
        glfwSwapInterval(static_cast<int>(this->vsync));
    };

    InputManager::getInstance().getInputMap().addPairing('v',v);*/

    windowMap[this->glfwWindow] = this;

    dynamic_cast<Subject<uint32_t ,uint32_t>*>(&InputManager::getInstance())->attach(this);
}

void Window::toggleVsync() {
    this->vsync = !this->vsync;
    glfwMakeContextCurrent(this->glfwWindow);
    glfwSwapInterval(static_cast<int>(this->vsync));
}

void Window::toggleFullscreen() {
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int wWidth = mode->width;
    int wHeight = mode->height;

    this->fullscreen ^= this->fullscreen;
    glfwMakeContextCurrent(this->glfwWindow);
    glfwSetWindowMonitor(this->glfwWindow,this->fullscreen ? glfwGetPrimaryMonitor() : NULL ,0,0,wWidth,wHeight,GLFW_DONT_CARE);
    delete mode;
}

void Window::use() {
    glfwMakeContextCurrent(this->glfwWindow);
}

const GLFWwindow &Window::getGlfwWindow() const {
    return *this->glfwWindow;
}

GLFWwindow &Window::getGlfwWindow() {
    return *this->glfwWindow;
}

bool Window::shouldClose() const{
    return glfwWindowShouldClose(this->glfwWindow);
}

void Window::swapBuffers() const {
    glfwSwapBuffers(this->glfwWindow);
}

void Window::update(uint32_t keyCode, uint32_t action) {
    if (keyCode == GLFW_KEY_C && action == GLFW_PRESS){
        this->toggleCursorLock();
    }
}

glm::vec<2, int> Window::getDimensions() const {
    return glm::vec<2, int>{this->width,this->height};
}

void Window::toggleCursorLock() {
    this->cursorLock = !this->cursorLock;

    if (this->cursorLock)
        glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}