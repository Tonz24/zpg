#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "LerpMaterial.h"
#include "TextureMaterial.h"
#include "ColorMaterial.h"
#include "Camera.h"
#include "Renderable.h"
#include "Transformation.h"
#include "Sphere.h"
#include "Monkey.h"
#include "Cube.h"

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

    Model* sphere = new Sphere();
    Model* monkey = new Monkey();
    Model* cube = new Cube();

    Controller* c = new Controller(100,2000);

    //generate shapes with random positions and materials
    for (int i = 0; i < 10; ++i) {
        Material* colorMat = new ColorMaterial({rng(gen), rng(gen), rng(gen)});
        Material* mat = new Material();
        Material* lerpMat = new LerpMaterial({rng(gen), rng(gen), rng(gen)}, {rng(gen), rng(gen), rng(gen)});

        TransformationComposite* t = new TransformationComposite();
        t->addTransformation({new Translation({i * 0.2f, rng(gen), 0}), new Rotation(rng(gen) * 360, {rng(gen), rng(gen), rng(gen)}), new Scale(glm::vec3{rng(gen) / 5})});

        Renderable* renderable = new Renderable(rng(gen) < 0.3f ? cube : (rng(gen) < 0.6f ? monkey : sphere), rng(gen) > 0.5f ? mat : material, t, c);
        Application::getInstance().getScene().addModel(*renderable);
    }

    Camera camera{};
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094