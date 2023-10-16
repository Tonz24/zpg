#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "LerpMaterial.h"
#include "TextureMaterial.h"
#include "ColorMaterial.h"
#include "Renderable.h"
#include "Transformation.h"
#include "Sphere.h"
#include "Monkey.h"
#include "Cube.h"
#include "Camera.h"
#include "PhongMaterial.h"
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
    Material* phong = new PhongMaterial({1,1,1},50.0f);

    Model* sphere = new Sphere();
    Model* monkey = new Monkey();
    Model* cube = new Cube();

    TransformationComposite* test = new TransformationComposite();
    test->addTransformation(new Translation({0,0,0}));

    TransformationComposite* test2 = new TransformationComposite();
    test->addTransformation(new Translation({10,0,0}));

    Light* l = new Light(glm::vec3{1,0,0},test);
    Light* l2 = new Light(glm::vec3{0,0,1},test2);

    Application::getInstance().getScene().addModel(*l);
    Application::getInstance().getScene().addModel(*l2);

    int ctrCount = 5;
    int size = 15;
    //generate shapes with random positions and materials
    for (int i = 2; i < ctrCount; ++i) {
        TransformationComposite* t = new TransformationComposite();
        t->addTransformation({new Translation({(i / (float)ctrCount) * size, rng(gen), 0})});
        float r = rng(gen);
        Renderable* renderable = new Renderable(sphere,  phong , t);
        Application::getInstance().getScene().addModel(*renderable);
    }

    Camera* cam = new Camera();
    cam->uploadMatrices();
    Application::getInstance().getScene().setCamera(cam);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094