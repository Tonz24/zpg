#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "Renderable.h"
#include "Transformation.h"
#include "Sphere.h"
#include "Monkey.h"
#include "Cube.h"
#include "Camera.h"
#include "PointLight.h"
#include "SpotLight.h"


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

    Material* phong = new PhongMaterial(glm::vec3{1, 0.3, 1}, 16.0f, 0.1f,0.5f);
    auto* sphere = new Sphere();

    Light* light = new PointLight(glm::vec3{2,1,2},sphere);
    scene->addModel(std::shared_ptr<Light>(light));

    Renderable* model = new Renderable(sphere,phong);

    model->setTranslation({5,0,0});
    scene->addModel(std::shared_ptr<Renderable>(model));
    scene->addModel(std::shared_ptr<Renderable>(model));

    return std::move(scene);

}

std::unique_ptr<Scene> setupScene2(){
    auto scene = std::make_unique<Scene>();

    auto* phong = new PhongMaterial(glm::vec3{1, 0.6, 1}, 16.0f, 0.1f,0.5f);
    auto* sphere = new Sphere();

    auto light = new PointLight(glm::vec3{1.5,1.5,1.5},sphere);
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));


    auto model = new Renderable(sphere,phong);
    auto model2 = new Renderable(sphere,phong);
    auto model3 = new Renderable(sphere,phong);
    auto model4 = new Renderable(sphere,phong);

    model->setTranslation({5,0,0});
    model2->setTranslation({-5,0,0});
    model3->setTranslation({0,5,0});
    model4->setTranslation({0,-5,0});

    scene->addModel(std::shared_ptr<Renderable>(model));
    scene->addModel(std::shared_ptr<Renderable>(model2));
    scene->addModel(std::shared_ptr<Renderable>(model3));
    scene->addModel(std::shared_ptr<Renderable>(model4));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene3(){

    auto scene = std::make_unique<Scene>();

    Material* constant = new ConstantMaterial(glm::vec3{0.4,0.7,1});
    Material* lambert = new LambertMaterial(glm::vec3{1, 1, 1},0.1);
    Material* phong = new PhongMaterial(glm::vec3{0, 1, 1});
    Material* blinn = new BlinnMaterial(glm::vec3{0.7, 0.2f, 1});

    std::vector<Material*> materials = {constant,lambert,phong,blinn};

    Sphere* sphere = new Sphere();
    Monkey* monkey = new Monkey();
    Cube* cube = new Cube();

    std::vector<Model*> models = {sphere,monkey,cube};

    auto light = new PointLight(glm::vec3{1.2,0.4,1.7},sphere);
    light->setTranslation({5,0,5});
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));
    auto light2 = new PointLight(glm::vec3{0.7,1.7,1.2},sphere);
    light2->setTranslation({5,0,0});
    light2->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light2));


    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            auto model = new Renderable(models[ (i + j) % models.size()],materials[ (i + j) % materials.size()]);
            model->setTranslation({i*2,-3,j*2});
            scene->addModel(std::shared_ptr<Renderable>(model));
        }
    }


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

    Application::getInstance().setScene(scene3);

    Application::getInstance().setUsePostFX(true);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094