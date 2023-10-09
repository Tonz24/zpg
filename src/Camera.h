//
// Created by Tonz on 02.10.2023.
//

#pragma once
#include "iostream"

#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"

#include "InputManager.h"
#include "Observer.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.0f;
const float SENSITIVITY = 0.03f;
const float ZOOM = 50.0f;

//learnopengl.com/Getting-started/Camera
class Camera : public Observer<int,int>{
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    [[nodiscard]]glm::mat4 getViewMatrix() const;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    void uploadMatrices() const;

    void update(int width, int height) override;

    void setAspect(const float& aspect);
    void setFov(const float& fov);
    void setNearPlane(const float& nearPlane);
    void setFarPlane(const float& farPlane);

private:
    glm::vec3 pos{0,0,0};
    glm::vec3 front{0,0,-1};
    glm::vec3 up{0,1,0};
    glm::vec3 right{1,0,0};
    glm::vec3 worldUp{0,1,0};

    float aspect{16.0f/9.0f};
    float fov{60.0f};
    float nearPlane{0.001f};
    float farPlane{150.0f};

    void updateProjectionMatrix();

    float yaw{180};
    float pitch{0};

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateCameraVectors();

    void initalizeCallbackLambdas();

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
};