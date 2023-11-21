#include <cstdio>
#include <random>

#include "Application.h"

#include "Texture.h"
#include "SceneObject.h"
#include "Models/Sphere.h"
#include "Models/Monkey.h"
#include "Models/Tree.h"
#include "Models/Cube.h"
#include "Camera.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"


#include "Materials/ConstantMaterial.h"
#include "Materials/LambertMaterial.h"
#include "Materials/PhongMaterial.h"
#include "Materials/BlinnMaterial.h"
#include "Models/Bush.h"
#include "Models/Quad.h"
#include "Materials/FurMaterial.h"
#include "Lights/DirectionalLight.h"
#include "Materials/SkyboxMaterial.h"
#include "Materials/PBMaterial.h"


static void error_callback(int error, const char* description){ fputs(description, stderr); }

static void window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height){
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

std::unique_ptr<Scene> setupScene1(){
    auto scene = std::make_unique<Scene>();

    auto* phong = new PhongMaterial(glm::vec3{1, 0.6, 1});
    auto* blinn = new BlinnMaterial(glm::vec3{1, 1, 0.6});

    auto tex = std::make_shared<Texture>("container.png");
    auto spec = std::make_shared<Texture>("container_specular.png");

    phong->setDiffuseMap(tex);
    phong->setSpecularMap(spec);

    auto* sphere = new Cube();

    auto light = new PointLight(glm::vec3{1.2,1.2,1.2},sphere);
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));

    auto model = new SceneObject(sphere, phong);
    auto model2 = new SceneObject(sphere, phong);
    auto model3 = new SceneObject(sphere, phong);
    auto model4 = new SceneObject(sphere, phong);

    model->setTranslation({3,0,0});
    model2->setTranslation({-3,0,0});
    model3->setTranslation({0,3,0});
    model4->setTranslation({0,-3,0});

    model->applyTransform();
    model2->applyTransform();
    model3->applyTransform();
    model4->applyTransform();

    scene->addModel(std::shared_ptr<SceneObject>(model));
    scene->addModel(std::shared_ptr<SceneObject>(model2));
    scene->addModel(std::shared_ptr<SceneObject>(model3));
    scene->addModel(std::shared_ptr<SceneObject>(model4));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene2(){
    auto scene = std::make_unique<Scene>();

    auto* m = new PhongMaterial(glm::vec3{0.5, 0.5, 0.5});
    auto* v = new PhongMaterial(glm::vec3{0.89020, 0.73333, 0.46275});
    auto* e = new PhongMaterial(glm::vec3{0.41961,  0.57647,  0.83922});
    auto* mo = new PhongMaterial(glm::vec3{0.90588,  0.90980,  0.92549});
    auto* ma = new PhongMaterial(glm::vec3{1.3,  0.9,  1.2});

    auto* sphere = new Sphere();

    auto light = new PointLight(glm::vec3{2,2,2},sphere);
    //light->setCanCastRays(false);
    light->setScale({2,2,2});
    light->setAttenuation({1,0.01,0.01});
    scene->addModel(std::shared_ptr<Light>(light));

    auto mercury = new SceneObject(sphere, m);
    auto venus = new SceneObject(sphere, v);
    //venus->setCanCastRays(true);
    auto earth = new SceneObject(sphere, e);
    //earth->setCanCastRays(true);
    auto moon = new SceneObject(sphere, mo);

    auto mars = new SceneObject(sphere, ma);
    //mars->setCanCastRays(true);
    auto phobos = new SceneObject(sphere, mo);
    auto deimos = new SceneObject(sphere, mo);

    mercury->setTranslation({5, 0, 0});
    mercury->setScale({0.33f,0.33f,0.33f});

    mercury->setTickFunction([mercury](){
        mercury->setRotateAround(glfwGetTime() * 25 + 100, {0, 0, 0}, {0, 1, 0});
        mercury->applyTransform();
    });

    venus->setTranslation({10, 0, 0});
    venus->setScale({0.78f,0.78f,0.78f});
    venus->setTickFunction([venus](){
        venus->setRotateAround(glfwGetTime() * 20 + 33, {0, 0, 0}, {0, 1, 0});
        venus->applyTransform();
    });

    earth->setTranslation({15, 0, 0});
    earth->addChild(std::unique_ptr<SceneObject>(moon));
    earth->setTickFunction([earth](){
        earth->setRotateAround(glfwGetTime() * 15 + 10, {0, 0, 0}, {0, 1, 0});
        earth->applyTransform();
    });

    moon->setTranslation({2,0,0});
    moon->setScale({0.15f,0.15f,0.15f});
    moon->applyTransform();

    moon->setTickFunction([moon](){
        moon->setRotateAround(glfwGetTime() * 60 + 8000, {0, 0, 0}, {0, 1, 0});
    });

    mars->setTranslation({20, 0, 0});
    mars->setScale({0.8,0.8,0.8});
    mars->addChild(std::unique_ptr<SceneObject>(phobos));
    mars->addChild(std::unique_ptr<SceneObject>(deimos));
    mars->setTickFunction([mars](){
        mars->setRotateAround(glfwGetTime() * 8 + 10588, {0, 0, 0}, {0, 1, 0});
        mars->applyTransform();
    });

    phobos->setTranslation({1.5,0,0});
    phobos->setScale({0.15f,0.15f,0.15f});
    phobos->applyTransform();

    phobos->setTickFunction([phobos](){
        phobos->setRotateAround(glfwGetTime() * 75 + 256, {0, 0, 0}, {0, 1, 0});
    });


    deimos->setTranslation({2,0,0});
    deimos->setScale({0.1f,0.1f,0.1f});
    deimos->applyTransform();

    deimos->setTickFunction([deimos](){
        deimos->setRotateAround(glfwGetTime() * 50 + 785, {0, 0, 0}, {0, 1, 0});
    });

    scene->addTickable(std::shared_ptr<ITickable>(mercury));
    scene->addTickable(std::shared_ptr<ITickable>(venus));
    scene->addTickable(std::shared_ptr<ITickable>(earth));
    scene->addTickable(std::shared_ptr<ITickable>(moon));
    scene->addTickable(std::shared_ptr<ITickable>(mars));
    scene->addTickable(std::shared_ptr<ITickable>(phobos));
    scene->addTickable(std::shared_ptr<ITickable>(deimos));


    scene->addModel(std::shared_ptr<SceneObject>(mercury));
    scene->addModel(std::shared_ptr<SceneObject>(venus));
    scene->addModel(std::shared_ptr<SceneObject>(earth));
    scene->addModel(std::shared_ptr<SceneObject>(moon));
    scene->addModel(std::shared_ptr<SceneObject>(mars));
    scene->addModel(std::shared_ptr<SceneObject>(phobos));
    scene->addModel(std::shared_ptr<SceneObject>(deimos));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene3(){
    auto scene = std::make_unique<Scene>();
    auto* phong = new PhongMaterial(glm::vec3{1, 0.6, 1},1,0.1,1);
    auto* sphere = new Sphere();

    auto light = new PointLight(glm::vec3{1.2,1.2,1.2},sphere);
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));

    auto model = new SceneObject(sphere, phong);

    model->setTranslation({3,0,0});
    model->applyTransform();

    scene->addModel(std::shared_ptr<SceneObject>(model));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene4(){
    auto scene = std::make_unique<Scene>();

    auto* phong = new PhongMaterial(glm::vec3{1, 0.6, 1});

    auto* sphere = new Sphere();


    auto light = new PointLight(glm::vec3{1.2,1.2,1.2},sphere);
    light->setScale({0.25,0.25,0.25});
    light->setTranslation({0,2,0});
    light->applyTransform();
    scene->addModel(std::shared_ptr<Light>(light));


    auto model = new SceneObject(sphere, phong);
    auto model2 = new SceneObject(sphere, phong);
    auto model3 = new SceneObject(sphere, phong);
    auto model4 = new SceneObject(sphere, phong);
    auto model5 = new SceneObject(sphere, phong);
    auto model6 = new SceneObject(sphere, phong);
    auto model7 = new SceneObject(sphere, phong);


    model->setTranslation({-6,0,0});
    model2->setTranslation({-4,0,0});
    model3->setTranslation({-2,0,0});
    model4->setTranslation({0,0,0});
    model5->setTranslation({2,0,0});
    model6->setTranslation({4,0,0});
    model7->setTranslation({6,0,0});

    model->applyTransform();
    model2->applyTransform();
    model3->applyTransform();
    model4->applyTransform();
    model5->applyTransform();
    model6->applyTransform();
    model7->applyTransform();

    scene->addModel(std::shared_ptr<SceneObject>(model));
    scene->addModel(std::shared_ptr<SceneObject>(model2));
    scene->addModel(std::shared_ptr<SceneObject>(model3));
    scene->addModel(std::shared_ptr<SceneObject>(model4));
    scene->addModel(std::shared_ptr<SceneObject>(model5));
    scene->addModel(std::shared_ptr<SceneObject>(model6));
    scene->addModel(std::shared_ptr<SceneObject>(model7));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene5(){
    auto scene = std::make_unique<Scene>();

    ConstantMaterial* constant = new ConstantMaterial(glm::vec3{0.4,0.7,1});
    LambertMaterial* lambert = new LambertMaterial(glm::vec3{1, 1, 0.3});
    PhongMaterial* phong = new PhongMaterial(glm::vec3{0.159, 0.553, 1.0});
    BlinnMaterial* blinn = new BlinnMaterial(glm::vec3{0.7, 0.2f, 1});
    PBMaterial* pbr = new PBMaterial(glm::vec3{0.7, 0.2f, 1}, 0.5, 0.4f);

    std::vector<ConstantMaterial*> materials = {lambert,phong};

    auto tex = std::make_shared<Texture>(R"(container.png)");
    auto spec = std::make_shared<Texture>("container_specular.png");
    lambert->setDiffuseMap(tex);
    phong->setDiffuseMap(tex);
    phong->setSpecularMap(spec);


    auto albedo = std::make_shared<Texture>(R"(rusted\rustediron2_basecolor.png)");
    auto metallic = std::make_shared<Texture>(R"(rusted\rustediron2_metallic.png)");
    auto roughness = std::make_shared<Texture>(R"(rusted\rustediron2_roughness.png)");
    pbr->setTextures(albedo,roughness,metallic,nullptr);



    Sphere* sphere = new Sphere();
    Monkey* monkey = new Monkey();
    Model* z = new Model("zombie.obj");
    Model* h = new Model("model.obj");
    Tree* tree = new Tree();
    Bush* bush = new Bush();
    Quad* quad = new Quad();

    std::vector<Model*> models = {tree,sphere,monkey,z,h,bush};

    LambertMaterial* lambertGround = new LambertMaterial(glm::vec3{1, 1, 0.3});
    auto texGr = std::make_shared<Texture>("grass.png");
    auto texZ = std::make_shared<Texture>("zombie.png");
    auto texHouse = std::make_shared<Texture>("house.png");

    auto* zMat = new PhongMaterial(glm::vec3{5,5,5}*50.0f);
    auto* houseMat = new PhongMaterial(glm::vec3{5,5,5}*50.0f);
    houseMat->setDiffuseMap(texHouse);
    zMat->setDiffuseMap(texZ);

    lambertGround->setDiffuseMap(texGr);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            auto model = new SceneObject(tree,phong);
            model->translate({i * 10 + rand() % 5, 0, j * 10 + rand() % 5});
            model->rotate(rand() % 1000 * 0.01);
            model->applyTransform();
            scene->addModel(std::shared_ptr<SceneObject>(model));
        }
    }


    auto zomb = new SceneObject(z,zMat);
    zomb->translate({10,0,35});
    zomb->setRotation(90,{0,1,0});
    zomb->applyTransform();
    scene->addModel(std::shared_ptr<SceneObject>(zomb));

    auto model = new SceneObject(h,houseMat);
    model->translate({10, 0,50});
    model->rotate(rand() % 1000 * 0.01);
    model->applyTransform();
    scene->addModel(std::shared_ptr<SceneObject>(model));


    auto ground = new SceneObject(quad, lambertGround);

    ground->setScale({50,1,50});
    ground->setTranslation({50,0,50});
    ground->applyTransform();
    scene->addModel(std::shared_ptr<SceneObject>(ground));

    auto light = new PointLight(glm::vec3{1.5,1,0.7},sphere);
    //light->setAttenuation({1,0.1,0});
    light->translate({7, 1.5, 40});
    light->setScale({0.5,0.5,0.5});
    light->applyTransform();

    auto light2 = new PointLight(glm::vec3{0.3,1.5,0.7},sphere);
    //light->setAttenuation({1,0.1,0});
    //light2->setCanCastRays(false);
    light2->translate({10, 1.5, 40});
    light2->setScale({0.5,0.5,0.5});
    light2->applyTransform();

    std::shared_ptr<Light> dirLight = std::make_shared<DirectionalLight>(glm::vec3{0.05});
    dirLight->setTranslation(glm::vec3{50,-5,40});
    dirLight->applyTransform();
    dirLight->setCanCastRays(false);
    //scene->addModel(dirLight);

    scene->addModel(std::shared_ptr<Light>(light));
    scene->addModel(std::shared_ptr<Light>(light2));

    return std::move(scene);
}

std::unique_ptr<Scene> setupScene6(){
    auto scene = std::make_unique<Scene>();

    Material* phong = new FurMaterial(32,0.2,{20,20});

    auto* sphere = new Cube();
    auto* quad = new Quad();


    auto light = new PointLight(glm::vec3{1.2,1.2,1.2},sphere);
    light->setScale({0.25,0.25,0.25});
    scene->addModel(std::shared_ptr<Light>(light));

    auto model = new SceneObject(sphere, phong);

    /*model->setTickFunction([model](){
       model->setRotation(glfwGetTime()*20,{1,0,0});
       model->applyTransform();
    });*/

    model->setTranslation({0,-2,0});
    model->applyTransform();
    scene->addModel(std::shared_ptr<SceneObject>(model));
    //scene->addTickable(std::shared_ptr<ITickable>(model));
    return std::move(scene);
}

std::unique_ptr<Scene> setupScene7(){
    auto scene = std::make_unique<Scene>();

    Cube* cube = new Cube();

    int x{6}, y{4};
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            float metallic = x / (float)(i - 1);
            float roughness = y / (float)(j - 1);
            PBMaterial* pbr = new PBMaterial(glm::vec3{1}, roughness, metallic);
            auto model = new SceneObject(cube,pbr);

            model->setTranslation({i*2,j*2,0});
            model->applyTransform();
            scene->addModel(std::shared_ptr<SceneObject>(model));
        }
    }
    auto light = new PointLight(glm::vec3{20,20,20},cube);
    light->setTranslation(glm::vec3{50,3,50});
    light->applyTransform();

    scene->addModel(std::shared_ptr<Light>(light));

    return std::move(scene);
}

int main(){
    srand(time(NULL));
    Application::getInstance().initialize();

    auto cam = std::make_shared<Camera>();
    cam->setFarPlane(500);

    auto scene = setupScene1();
    auto scene2 = setupScene2();
    auto scene3 = setupScene3();
    auto scene4 = setupScene4();
    auto scene5 = setupScene5();
    auto scene6 = setupScene6();
    auto scene7 = setupScene7();

    auto flashLight = new SpotLight(glm::vec3{2,2,2});
    flashLight->setOuterCutoffAngle(25);
    flashLight->setInnerCutoffAngle(0);
    flashLight->setCanCastRays(false);
    //flashLight->setAttenuation({1,0.001f,0.0003f});
    scene5->addModel(std::shared_ptr<Light>(flashLight));

    flashLight->setTickFunction([flashLight, cam](){
        flashLight->setPosition(cam->getPos());
        flashLight->setDirection(cam->getFront());
    });
    scene5->addTickable(std::shared_ptr<ITickable>(flashLight));

    scene->addTickable(cam);
    scene2->addTickable(cam);
    scene3->addTickable(cam);
    scene4->addTickable(cam);
    scene5->addTickable(cam);
    scene6->addTickable(cam);
    scene7->addTickable(cam);

    scene->setActiveCamera(cam);
    scene2->setActiveCamera(cam);
    scene3->setActiveCamera(cam);
    scene4->setActiveCamera(cam);
    scene5->setActiveCamera(cam);
    scene6->setActiveCamera(cam);
    scene7->setActiveCamera(cam);

    auto skybox = std::make_shared<Skybox>("skybox_water");

    scene5->setSkybox(skybox);
    scene7->setSkybox(skybox);

    Application::getInstance().setScene(scene5); //2 //5

    Application::getInstance().setUsePostFX(true);
    Application::getInstance().run();
}
//RADEK MELČÁK MEL0094