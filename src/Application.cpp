//
// Created by Tonz on 26.09.2023.
//

#include <functional>

#include "Application.h"
#include "Shader.h"


void Application::initialize() {
    //glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    //inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = std::make_unique<Window>();

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetKeyCallback(&this->window->getGlfwWindow(),&InputManager::keyCallback);
    glfwSetCursorPosCallback(&this->window->getGlfwWindow(), &InputManager::cursorCallback);
    glfwSetMouseButtonCallback(&this->window->getGlfwWindow(), &InputManager::mouseButtonCallback);
    glfwSetCursorPosCallback(&this->window->getGlfwWindow(), &InputManager::cursorPositionCallback);
    /*glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    */

    // get version info
    printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    Shader::compileShaders();

    this->transformBuffer = std::make_unique<UBO>(sizeof(glm::mat4x4)*3 + sizeof(glm::vec4),5,nullptr);
    this->lightBuffer = std::make_unique<UBO>(sizeof(glm::vec4)*2*100 + sizeof(glm::vec4),6,nullptr);

    this->initialized = true;
}

Application::Application() {
    this->scene = std::make_unique<Scene>();
}

void Application::run() {
    if(!this->initialized) this->initialize();

    glClearColor(0.1f,0.1f,0.1f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    while (!this->window->shouldClose()){
        currentTime = getTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw();
        glfwPollEvents();
        this->window->swapBuffers();
    }
    this->terminate();
}

void Application::terminate() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

float Application::getTime() {
    return glfwGetTime();
}

float Application::getDeltaTime() {
    return deltaTime;
}

const UBO &Application::getTransformBuffer() const {
    return *this->transformBuffer;
}

const  Window& Application::getWindow() const {
    return *this->window;
}

Window &Application::getWindow() {
    return *this->window;
}

const UBO &Application::getLightBuffer() const {
    return *this->lightBuffer;
}
