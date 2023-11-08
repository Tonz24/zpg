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
const float SPEED = 5.0f;
const float SENSITIVITY = 0.03f;
const float ZOOM = 50.0f;

//learnopengl.com/Getting-started/Camera
class Camera : public ITickable, public Observer<int,int>, public Observer<uint32_t ,uint32_t>, public Observer<double,double,double,double>{
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    [[nodiscard]]const glm::mat4& getViewMatrix() const;
    [[nodiscard]]const glm::mat4& getProjMatrix() const{
        return this->projectionMatrix;
    }

    void processMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

    void uploadMatrices() const;

    void update(int width, int height) override;
    void update(uint32_t key, uint32_t action) override;

    void update(double x, double y, double dx, double dy) override;

    void setAspect(const float& aspect);
    void setFov(const float& fov);
    void setNearPlane(const float& nearPlane);
    void setFarPlane(const float& farPlane);

    void tick() override;

    [[nodiscard]] const glm::vec3 &getPos() const;
    [[nodiscard]] const glm::vec3 &getFront() const;

private:
    glm::vec3 velocity{0,0,0};

    glm::vec3 pos{0,0,0};
    glm::vec3 front{0,0,-1};
    glm::vec3 up{0,1,0};
    glm::vec3 right{1,0,0};
    glm::vec3 worldUp{0,1,0};

    float aspect{16.0f/9.0f};
    float fov{60.0f};
    float nearPlane{0.001f};
    float farPlane{150.0f};

    void updateViewMatrix();
    void updateProjectionMatrix();

    void uploadViewMatrix() const;
    void uploadProjectionMatrix() const;

    float yaw{180};
    float pitch{0};

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateCameraVectors();

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    glm::mat4 viewMatrix = glm::lookAt(pos,front,up);
};