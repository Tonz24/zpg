//
// Created by Tonz on 26.09.2023.
//

#include <functional>

#include "Application.h"
#include "Shader.h"
#include "ImageEffects/ColorFilter.h"
#include "ImageEffects/EmptyEffect.h"
#include "ImageEffects/Tonemap.h"


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
    this->lightBuffer = std::make_unique<UBO>(sizeof(glm::vec4)*3*30 + sizeof(glm::vec4)*4*30 +  sizeof(glm::vec4),6,nullptr);


    this->framebuffer[0] = new Framebuffer();
    this->framebuffer[1] = new Framebuffer();


    imageEffects.push_back(std::make_unique<ColorFilter>(glm::vec3{1,0,1}));

    finalEffect = std::make_unique<EmptyEffect>();


    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    this->initialized = true;
}

Application::Application() {
    this->scene = std::make_unique<Scene>();
}

void Application::run() {
    if(!this->initialized) this->initialize();

    glEnable(GL_CULL_FACE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!this->window->shouldClose()){
        currentTime = getTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        this->framebuffer[0]->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        scene->draw();
        glDisable(GL_DEPTH_TEST);

        int ping{0}, pong{1};
        for (int i = 0; i < imageEffects.size(); i++) {

            framebuffer[pong]->bind();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            imageEffects.at(i)->apply();

            glBindVertexArray(quadVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, framebuffer[ping]->getTargetId());
            glDrawArrays(GL_TRIANGLES, 0, 6);
            std::swap(ping,pong);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //finalEffect->apply();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->framebuffer[ping]->getTargetId());
        glDrawArrays(GL_TRIANGLES, 0, 6);

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