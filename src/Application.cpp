//
// Created by Tonz on 26.09.2023.
//

#include <functional>

#include "Application.h"
#include "Shader.h"
#include "InputManager.h"


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

    this->window = glfwCreateWindow(1000, 1080, "ZPG MELČÁK", NULL, NULL);
    if (!this->window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    std::function<void(int key)> tonda([](int key){std::cout << "franta" << std::endl;}) ;
    InputManager::getInstance().getInputMap().addPairing('H',tonda);

    glfwSetKeyCallback(window,&InputManager::keyCallback);
    glfwSetCursorPosCallback(window, &InputManager::cursorCallback);
    glfwSetMouseButtonCallback(window, &InputManager::mouseButtonCallback);
    glfwSetCursorPosCallback(window, &InputManager::cursorPositionCallback);
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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    Shader::compileShaders();

    this->transformBuffer = std::make_unique<UBO>(sizeof(glm::mat4x4)*3,5,nullptr);

    this->initialized = true;

}

Application::Application() {
    this->scene = std::make_unique<Scene>();
}

void Application::run() {
    if(!this->initialized) this->initialize();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)){
        currentTime = getTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw();
        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    this->terminate();
}

void Application::terminate() {
    glfwDestroyWindow(window);
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
