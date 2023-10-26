#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "Renderable.h"
#include "Sphere.h"
#include "Monkey.h"
#include "Cube.h"
#include "Camera.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"


#include "Materials/ConstantMaterial.h"
#include "Materials/LambertMaterial.h"
#include "Materials/PhongMaterial.h"
#include "Materials/BlinnMaterial.h"


static void error_callback(int error, const char* description){ fputs(description, stderr); }

static void window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height){
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}


std::unique_ptr<Scene> setupScene1(){
    auto scene = std::make_unique<Scene>();

    ConstantMaterial* phong = new PhongMaterial(glm::vec3{1, 1,1},1,0.1,4096,20);
    auto* sphere = new Sphere();
    auto* cube = new Cube();

    SpotLight* spotLight = new SpotLight({2,2,2},sphere);
    spotLight->setDirection({1,0,0});

    scene->addModel(std::shared_ptr<Light>(spotLight));

    Renderable* model = new Renderable(sphere,phong);
    model->setTickFunction([model](){
       model->setTranslation({5,0,sin(glfwGetTime())});
    });

    scene->addTickable(std::shared_ptr<ITickable>(model));

    Renderable* cubeModel = new Renderable(cube,phong);
    cubeModel->translate({8,0,0});
    cubeModel->setScale({0.1,100,100});

    scene->addModel(std::shared_ptr<Renderable>(model));
    scene->addModel(std::shared_ptr<Renderable>(cubeModel));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene2(){
    auto scene = std::make_unique<Scene>();

    auto* phong = new PhongMaterial(glm::vec3{1, 0.6, 1});
    ConstantMaterial* constant = new ConstantMaterial(glm::vec3{0.4,0.7,1});
    LambertMaterial* lambert = new LambertMaterial(glm::vec3{1, 1, 1},0.1);
    BlinnMaterial* blinn = new BlinnMaterial(glm::vec3{0.7, 0, 0});
    auto* sphere = new Sphere();
    auto* cube = new Cube();

    auto light = new PointLight(glm::vec3{1.5,1.5,1.5},sphere);
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));


    auto model = new Renderable(cube,constant);
    auto model2 = new Renderable(sphere,constant);
    auto model3 = new Renderable(sphere,constant);
    auto model4 = new Renderable(sphere,constant);

    model->setTranslation({1,0,0});

    model->setTickFunction([model]() mutable{
        model->setRotateAround(glfwGetTime()*100.0f,{0,0,0},{0,1,0});
    });

    scene->addTickable(std::shared_ptr<ITickable>(model));

    model2->setTranslation({-5,0,0});
    model3->setTranslation({0,5,0});
    model4->setTranslation({0,0,-5});

    scene->addModel(std::shared_ptr<Renderable>(model));
    scene->addModel(std::shared_ptr<Renderable>(model2));
    scene->addModel(std::shared_ptr<Renderable>(model3));
    scene->addModel(std::shared_ptr<Renderable>(model4));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene3(){

    auto scene = std::make_unique<Scene>();

    ConstantMaterial* constant = new ConstantMaterial(glm::vec3{0.4,0.7,1});
    ConstantMaterial* lambert = new LambertMaterial(glm::vec3{1, 1, 1},0.1);
    ConstantMaterial* phong = new PhongMaterial(glm::vec3{0, 1, 1});
    ConstantMaterial* blinn = new BlinnMaterial(glm::vec3{0.7, 0.2f, 1});

    std::vector<ConstantMaterial*> materials = {constant,lambert,phong,blinn};

    Sphere* sphere = new Sphere();
    Monkey* monkey = new Monkey();
    Cube* cube = new Cube();

    std::vector<Model*> models = {sphere,monkey,cube};

    auto light = new PointLight(glm::vec3{1.7,0,0},sphere);
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));

    auto light2 = new PointLight(glm::vec3{0,1.7,0},sphere);
    light2->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light2));

    auto light3 = new PointLight(glm::vec3{0,0,1.7},sphere);
    light3->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light3));

    light->setTickFunction([light](){
       light->setTranslation({sin(glfwGetTime() + 2.094)*5 + 5,0,cos(glfwGetTime() + 2.094)*5 + 5});
    });

    light2->setTickFunction([light2](){
        light2->setTranslation({sin(glfwGetTime())*5 + 5,0,cos(glfwGetTime())*5 + 5});
    });

    light3->setTickFunction([light3](){
        light3->setTranslation({sin(glfwGetTime() + 2.094*2)*5 + 5 ,0,cos(glfwGetTime() + 2.094*2)*5 + 5 });
    });

    scene->addTickable(std::shared_ptr<ITickable>(light));
    scene->addTickable(std::shared_ptr<ITickable>(light2));
    scene->addTickable(std::shared_ptr<ITickable>(light3));

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            auto model = new Renderable(models[ (i + j) % models.size()],materials[ (i + j) % materials.size()]);
            model->setTranslation({i*2,-3,j*2});
            scene->addModel(std::shared_ptr<Renderable>(model));

            model->setTickFunction([model, i, j]() mutable{
               model->setScale({sin(glfwGetTime()/2.0 + i + j)*0.5 + 0.5 + 0.1,1.0,sin(glfwGetTime()/2.0 + i - j)*0.5 + 0.5 + 0.1});
            });
            scene->addTickable(std::shared_ptr<ITickable>(model));
        }
    }

    ConstantMaterial* phong2 = new BlinnMaterial(glm::vec3{1, 1, 1},1,0.1);
    auto model = new Renderable(cube,phong2);
    model->setTranslation({0,-5,0});
    model->setScale({100,0.05,100});
    scene->addModel(std::shared_ptr<Renderable>(model));

    return std::move(scene);
}

int main(){
    Application::getInstance().initialize();

    auto cam = std::make_shared<Camera>();

    auto scene = setupScene1();
    auto scene2 = setupScene2();
    auto scene3 = setupScene3();

    scene->addTickable(cam);
    scene2->addTickable(cam);
    scene3->addTickable(cam);

    scene->setActiveCamera(cam);
    scene2->setActiveCamera(cam);
    scene3->setActiveCamera(cam);
    Application::getInstance().setScene(scene3);

    Application::getInstance().setUsePostFX(true);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094