//Include GLFW  
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <cstdio>
#include <random>

#include "Application.h"
//#include "Quad.h"
//#include "Triangle.h"

#include "Texture.h"
#include "LerpMaterial.h"
#include "TextureMaterial.h"
#include "ColorMaterial.h"
#include "Camera.h"
#include "Renderable.h"

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
    std::uniform_real_distribution<float> uni(-1, 1);
    std::uniform_real_distribution<float> uniColor(0, 1);

    Texture tex("cock.png");
    Material* material = new TextureMaterial(tex);

    Model* model = new Model(VertexType(VertexType::VertexTypeEnum::POS | VertexType::VertexTypeEnum::NORMAL));

    //generate shapes with random positions and materials
    for (int i = 0; i < 1; ++i) {
        Material* colorMat = new ColorMaterial({uniColor(gen),uniColor(gen),uniColor(gen)});
        Material* mat = new Material();
        Material* lerpMat = new LerpMaterial({uniColor(gen),uniColor(gen),uniColor(gen)},{uniColor(gen),uniColor(gen),uniColor(gen)});

        Renderable* renderable = new Renderable(model,mat);
        renderable->getTransform().setScale({0.5,0.5,0.5});

        Application::getInstance().getScene().addModel(*renderable);
    }
    Camera camera{};
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094