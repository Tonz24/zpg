//
// Created by Tonz on 02.10.2023.
//

#include "Application.h"
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): pos(position), worldUp(up), yaw(yaw), pitch(pitch),
        movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM){

    Application::getInstance().getWindow().attach(this);
    InputManager::getInstance().attach(this);
    this->initalizeCallbackLambdas();
    this->updateCameraVectors();

    this->uploadViewMatrix();
    this->uploadProjectionMatrix();
}

const glm::mat4& Camera::getViewMatrix() const{
    return this->viewMatrix;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch){

    yaw += xoffset * mouseSensitivity;
    pitch += yoffset * mouseSensitivity;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    // update front, right and up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset){
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::updateProjectionMatrix() {
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->aspect, this->nearPlane, this->farPlane);
    this->uploadProjectionMatrix();
}

void Camera::updateViewMatrix() {
    this->viewMatrix = glm::lookAt(this->pos,this->pos + this->front,this->up);
    this->uploadViewMatrix();
}

void Camera::updateCameraVectors(){
    // calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    // also re-calculate the right and up vector
    this->right = glm::normalize(glm::cross(this->front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->up = glm::normalize(glm::cross(right, this->front));

    this->updateViewMatrix();
}

void Camera::uploadMatrices() const {
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),sizeof(glm::mat4x4),&this->viewMatrix);
}

void Camera::setAspect(const float& aspect) {
    this->aspect = aspect;
    this->updateProjectionMatrix();
}
void Camera::setFov(const float& fov) {
    this->fov = fov;
    this->updateProjectionMatrix();
}
void Camera::setNearPlane(const float& nearPlane) {
    this->nearPlane = nearPlane;
    this->updateProjectionMatrix();
}
void Camera::setFarPlane(const float& farPlane) {
    this->farPlane = farPlane;
    this->updateProjectionMatrix();
}

void Camera::initalizeCallbackLambdas() {
    std::function<void(double,double,double,double)> mouseMovement = [this](double x, double y, double dx, double dy){
        dx *= mouseSensitivity;
        dy *= mouseSensitivity;

        this->yaw += dx;
        this->pitch -= dy;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;

        if (this->pitch < -89.0f)
            this->pitch = -89.0f;

        // update front, right and up Vectors using the updated Euler angles
        this->updateCameraVectors();
    };
    InputManager::getInstance().registerMouseCallback(mouseMovement);
}

void Camera::update(int width, int height) {
    std::cout << width << " " << height << std::endl;
    this->setAspect(static_cast<float>(width) / static_cast<float>(height));
}

void Camera::uploadViewMatrix() const {
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4),sizeof(glm::mat4x4),glm::value_ptr(this->viewMatrix));
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4)*3,sizeof(glm::vec4),&this->pos);
}

void Camera::uploadProjectionMatrix() const {
    Application::getInstance().getTransformBuffer().setData(sizeof(glm::mat4x4)*2,sizeof(glm::mat4x4),glm::value_ptr(this->projectionMatrix));
}

void Camera::update(uint32_t key, uint32_t action) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        this->velocity.z += 1;

    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        this->velocity.z -= 1;


    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        this->velocity.z += -1;

    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        this->velocity.z -= -1;


    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        this->velocity.x += -1;

    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        this->velocity.x -= -1;


    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        this->velocity.x += 1;

    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        this->velocity.x -= 1;
}

void Camera::tick() {
    glm::vec3 oldPos = this->pos;
    this->pos += this->front * this->velocity.z * Application::getInstance().getDeltaTime();
    this->pos += this->right * this->velocity.x * Application::getInstance().getDeltaTime();

    if (this->pos != oldPos)
        this->updateViewMatrix();
}