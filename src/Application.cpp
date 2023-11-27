//
// Created by Tonz on 26.09.2023.
//

#include <functional>

#include "Application.h"
#include "ShaderProgram.h"
#include "PostProcessing/Tonemap.h"
#include "PostProcessing/PostFX.h"
#include "PostProcessing/BloomEffect.h"
#include "PostProcessing/LightShaft.h"
#include "Materials/FurMaterial.h"

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

    ShaderProgram::compileShaders();

    this->transformBuffer = std::make_unique<UBO>(sizeof(glm::mat4x4)*4 + sizeof(glm::vec4),5,nullptr);
    this->lightBuffer = std::make_unique<UBO>(48*30 + 64*30 + 112*30 + 16,6,nullptr);


    PostFX::getInstance().addEffect(new BloomEffect(10));
    PostFX::getInstance().addEffect(new LightShaft());
    PostFX::getInstance().addEffect(new TonemapACES());


    this->shadowMapShader = ShaderProgram::getShaderProgram("shader_shadowMap");


    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    this->initialized = true;

    dynamic_cast<Subject<uint32_t,uint32_t,glm::vec2>*>(&InputManager::getInstance())->attach(this);
}

Application::Application() {
    this->scene = std::make_unique<Scene>();
}

void Application::run() {
    if(!this->initialized) this->initialize();

    //glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!this->window->shouldClose()){
        currentTime = getTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;


        if(this->usePostFX) {
            PostFX::getInstance().bindPing();
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            scene->draw();
            glDisable(GL_DEPTH_TEST);
            PostFX::getInstance().applyEffects();
        }
        else{
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            scene->drawNoFX();
        }

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

void Application::setUsePostFX(bool value) {
    this->usePostFX = value;
}

void Application::setScene(std::unique_ptr<Scene> &scene) {
    scene->activateLights();
    this->scene->deactivateLights();
    this->scene.swap(scene);
}

const void Application::bindShadowMapShader() {
    this->shadowMapShader->bind();
}

bool Application::getUsePostFx() const {
    return usePostFX;
}

void Application::update(uint32_t button, uint32_t action, glm::vec2 pos) {
    if (action == GLFW_PRESS){
        Application& instance = Application::getInstance();

        pos.y = instance.getWindow().getHeight() - pos.y;

        uint32_t id{300};
        float depth{0};

        glReadPixels(pos.x, pos.y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &id);
        glReadPixels(pos.x, pos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

        glm::vec3 screenX{pos.x,pos.y,depth};

        glm::mat4 view{instance.getScene().getActiveCamera().getViewMatrix()};
        glm::mat4 proj{instance.getScene().getActiveCamera().getProjMatrix()};

        glm::vec4 viewPort{0,0,instance.getWindow().getWidth(),instance.getWindow().getHeight()};

        glm::vec3 globalPos = glm::unProject(screenX,view,proj,viewPort);

        Scene& scene = instance.getScene();

        FurMaterial* fur = new FurMaterial(50,0.035f,{1000,1000});

        Model* h = new Model("zombie.obj");

        auto model = new SceneObject(h,fur);

        model->setTranslation(globalPos);
        model->applyTransform();

        scene.addModel(std::shared_ptr<SceneObject>(model));

    }
}