//
// Created by Tonz on 03.10.2023.
//

#include "SceneObject.h"
#include "Application.h"

void SceneObject::draw() {
    this->material->uploadVariables();
    this->uploadModelMatrix();
    if (model.get() != nullptr)
        this->model->draw();
}

void SceneObject::drawForShadowMapping() {
    this->uploadModelMatrix();
    if (model.get() != nullptr)
        this->model->draw();
}

void SceneObject::uploadModelMatrix(){
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),glm::value_ptr(this->modelMat));
    glm::mat4x4 normalMatrix = glm::transpose(glm::inverse(this->modelMat));
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4)*3,sizeof(glm::mat4x4),glm::value_ptr(normalMatrix));
}

SceneObject::SceneObject(Model *model, Material *material): model(std::shared_ptr<Model>(model)), material(std::shared_ptr<Material>(material)), IDrawable(){

    this->translation = new Translation();
    this->rotation = new Rotation();
    this->scale = new Scale();
    this->rotateAroundPoint = new RotateAroundPoint();

    this->transform = std::make_unique<TransformationComposite>();
    this->transform->addTransformation({this->translation,this->rotateAroundPoint,this->rotation,this->scale});
}

void SceneObject::tick() {
    ITickable::tick();
}

void SceneObject::setTranslation(const glm::vec3 &translation) {
    this->translation->setTranslation(translation);
    //this->applyTransform();
}

void SceneObject::translate(const glm::vec3 &translation) {
    this->translation->translate(translation);
    //this->applyTransform();
}

void SceneObject::setScale(const glm::vec3 &scale) {
    this->scale->setScale(scale);
    //this->applyTransform();
}

void SceneObject::setRotation(const float& angle, const glm::vec3& axis) {
    this->rotation->setRotation(angle,axis);
    //this->applyTransform();
}

void SceneObject::rotate(const float &angle) {
    this->rotation->rotate(angle);
    //this->applyTransform();
}


const Material &SceneObject::getMaterial()const {
    return *this->material;
}
void SceneObject::setRotateAround(float angle, const glm::vec3& point, const glm::vec3& axis){
    this->rotateAroundPoint->setRotation(angle);
    this->rotateAroundPoint->setPoint(point);
    this->rotateAroundPoint->setAxis(axis);
    //this->applyTransform();
}

void SceneObject::rotateAround(float angle) {
    this->rotateAroundPoint->rotate(angle);
    //this->applyTransform();
}

const glm::vec3 &SceneObject::getTranslation() const {
    return this->translation->getTranslation();
}

void SceneObject::applyTransform() {
    this->modelMat = glm::mat4{1};
    this->transform->apply(modelMat);

    for (auto &child : this->children){
        child->applyTransform(this->modelMat);
    }
}

void SceneObject::applyTransform(const glm::mat4 &modelMat) {
    this->modelMat = glm::mat4{1};
    this->transform->apply(this->modelMat);

    this->modelMat = modelMat * this->modelMat;

    for (auto &child : this->children){
        child->applyTransform(this->modelMat);
    }
}

SceneObject::SceneObject(const std::string &path) : IDrawable() {
    this->model = std::make_shared<Model>(path);
}


