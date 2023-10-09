//
// Created by Tonz on 09.10.2023.
//
#pragma once
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>

class Window {
public:
    explicit Window(const uint32_t& width = 800, const uint32_t& height = 600, const std::string& name = "Window");
    [[nodiscard]] float getAspectRatio() const;

    void toggleFullscreen();
    void toggleVsync();
    void use();
    [[nodiscard]] bool shouldClose() const;
    void swapBuffers() const;

    [[nodiscard]] const GLFWwindow& getGlfwWindow() const;
    [[nodiscard]] GLFWwindow& getGlfwWindow();

private:
    GLFWwindow* glfwWindow;

    uint32_t width;
    uint32_t height;
    std::string name;

    bool vsync{true};
    bool fullscreen{false};

    static void window_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
    }
};