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

int main(){
    Application::getInstance().initialize();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rng(0, 1);

    Texture tex("cock.png");
    Material* constant = new ConstantMaterial({1, 0.5, 0});
    Material* blinn = new BlinnMaterial({1, 1, 1}, 32.0f, 0.2f, 5);
    Material* lamb = new LambertMaterial({1, 0.7, 1},1.0f);
    Material* phong = new PhongMaterial({1, 1, 1}, 64.0f, 0.2f,0.5f);

    Model* sphere = new Sphere();
    Model* monkey = new Monkey();
    Model* cube = new Cube();

    auto l = std::make_shared<PointLight>(glm::vec3{2.2,0.7,0.7});

    l->setTranslation({5,5,5});
    Application::getInstance().getScene().addModel(l);

    auto l4 = std::make_shared<SpotLight>(glm::vec3{10,10,10});
    l4->setCutoffAngle(25.0f);

    int ctrCount = 5;
    int size = 10;
    //generate shapes with random positions and materials
    for (int i = 0; i < ctrCount; ++i) {
        for (int j = 0; j < ctrCount; j++){
            auto renderable = std::make_shared<Renderable>(monkey, phong);
            renderable->setTranslation({i*2 ,0, j*2});
            Application::getInstance().getScene().addModel(renderable);
        }
    }

    auto cam = std::make_shared<Camera>();
    Application::getInstance().getScene().setCamera(cam);
    Application::getInstance().getScene().addTickable(cam);


    l4->setTickFunction([&](){
        l4->setDirection(cam->getFront());
        l4->setPosition(cam->getPos());
    });

    Application::getInstance().setUsePostFX(true);
    Application::getInstance().getScene().addTickable(l4);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094