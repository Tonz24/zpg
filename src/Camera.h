//
// Created by Tonz on 02.10.2023.
//

#pragma once
#include "iostream"

#include "glm.hpp"
#include "InputManager.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"


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

const glm::mat4 projPersp = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.01f, 150.0f);

//learnopengl.com/Getting-started/Camera
class Camera{
public:

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 GetViewMatrix() const;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    void setProjectionMatrix(glm::mat4 projectionMatrix);
    glm::mat4 getProjectionMatrix();

private:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    void updateCameraVectors();

    glm::mat4 projectionMatrix;
};

