#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "Materials/TextureMaterial.h"
#include "Materials/ColorMaterial.h"
#include "Renderable.h"
#include "Transformation.h"
#include "Sphere.h"
#include "Monkey.h"
#include "Cube.h"
#include "Tree.h"
#include "Camera.h"
#include "Materials/BlinnMaterial.h"
#include "PointLight.h"
#include "SpotLight.h"

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
    Material* material = new TextureMaterial(tex);
    Material* blinn = new BlinnMaterial({1, 1, 1}, 32.0f, 0.2f, 5);
    Material* phong = new PhongMaterial({1, 1, 1}, 64.0f, 0.2f, 5);

    Model* sphere = new Sphere();
    Model* monkey = new Monkey();
    Model* cube = new Cube();
    Tree* tree = new Tree();

    auto* test = new TransformationComposite();
    test->addTransformation(new Translation({12,7,0}));
    auto* test2 = new TransformationComposite();
    test2->addTransformation(new Translation({0,7,0}));
    auto* test3 = new TransformationComposite();
    test3->addTransformation(new Translation({12,7,12}));

    auto l = std::make_shared<PointLight>(glm::vec3{0.2,5,0.7},test);
    auto l2 = std::make_shared<PointLight>(glm::vec3{0,1,0},test2);
    auto l3 = std::make_shared<PointLight>(glm::vec3{1,1,1},test3);

    auto l4 = std::make_shared<SpotLight>(glm::vec3{1,1,1},test3);
    //l4->setAttenuation({1,0,0});
    l4->setCutoffAngle(25.0f);

    /*l->setTickFunction([&l](){
        l->setColor(glm::vec3{0,cos(Application::getInstance().getTime()),sin(Application::getInstance().getTime())});
    });*/

    //Application::getInstance().getScene().addTickable(l);

    Application::getInstance().getScene().addModel(l4);
    Application::getInstance().getScene().addModel(l2);
    Application::getInstance().getScene().addModel(l);
    Application::getInstance().getScene().addModel(l3);

    int ctrCount = 10;
    int size = 10;
    //generate shapes with random positions and materials
    for (int i = 0; i < ctrCount; ++i) {
        for (int j = 0; j < ctrCount; j++){
            auto* t = new TransformationComposite();
            t->addTransformation(new Translation({(i / (float) ctrCount) * size, rng(gen), (j / (float) ctrCount) * size}));
            auto renderable = std::make_shared<Renderable>(cube, phong , t);
            Application::getInstance().getScene().addModel(renderable);
        }
    }

    auto cam = std::make_shared<Camera>();
    cam->uploadMatrices();
    Application::getInstance().getScene().setCamera(cam);
    Application::getInstance().getScene().addTickable(cam);

    l4->setDirection({0,-0.5,0});
    l4->setPosition({5,10,5});


    l4->setTickFunction([&](){
        l4->setDirection(cam->getFront());
        l4->setPosition(cam->getPos());
    });

    Application::getInstance().getScene().addTickable(l4);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094