#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "TextureMaterial.h"
#include "ColorMaterial.h"
#include "Renderable.h"
#include "Transformation.h"
#include "Sphere.h"
#include "Monkey.h"
#include "Cube.h"
#include "Camera.h"
#include "BlinnMaterial.h"
#include "Light.h"

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
    Material* blinn = new BlinnMaterial({1, 1, 1}, 32.0f, 0.2f, 1);
    Material* phong = new PhongMaterial({1, 1, 1}, 32.0f, 0.2f, 1);

    Model* sphere = new Sphere();
    Model* monkey = new Monkey();
    Model* cube = new Cube();

    auto* test = new TransformationComposite();
    test->addTransformation(new Translation({2,0,0}));

    auto* test2 = new TransformationComposite();
    test2->addTransformation(new Translation({10,5,0}));

    auto* test3 = new TransformationComposite();
    test3->addTransformation(new Translation({10,-5,0}));

    auto* l = new Light(glm::vec3{1,0,0},test);
    auto* l2 = new Light(glm::vec3{0,1,0},test2);
    auto* l3 = new Light(glm::vec3{0,0,1},test3);

    Application::getInstance().getScene().addModel(*l);
    Application::getInstance().getScene().addModel(*l2);
    Application::getInstance().getScene().addModel(*l3);

    int ctrCount = 10;
    int size = 30;
    //generate shapes with random positions and materials
    for (int i = 2; i < ctrCount; ++i) {
        auto* t = new TransformationComposite();
        t->addTransformation(new Translation({(i / (float)ctrCount) * size, rng(gen), 0}));
        auto* renderable = new Renderable(sphere, i % 2 == 0 ? blinn : phong , t);
        Application::getInstance().getScene().addModel(*renderable);
    }

    Camera* cam = new Camera();
    cam->uploadMatrices();
    Application::getInstance().getScene().setCamera(cam);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094