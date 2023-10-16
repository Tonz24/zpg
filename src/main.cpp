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
    Material* phong = new PhongMaterial({0,1,0},50.0f);

    Model* sphere = new Sphere();
    Model* monkey = new Monkey();
    Model* cube = new Cube();

    int ctrCount = 1;
    int size = 15;
    //generate shapes with random positions and materials
    for (int i = 0; i < ctrCount; ++i) {
        Material* colorMat = new ColorMaterial({rng(gen), rng(gen), rng(gen)});
        Material* mat = new Material();
        Material* lerpMat = new LerpMaterial({rng(gen), rng(gen), rng(gen)}, {rng(gen), rng(gen), rng(gen)});
        TransformationComposite* t = new TransformationComposite();
        t->addTransformation({new Translation({(i / (float)ctrCount) * size, rng(gen), 0}), new Scale({0.2,0.2,0.2})});
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