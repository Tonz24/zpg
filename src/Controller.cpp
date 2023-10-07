//
// Created by Tonz on 06.10.2023.
//

#include "Controller.h"
#include "InputManager.h"
#include "Application.h"

void Controller::applyPreTransform(glm::mat4 &matrix) {
    this->preTransform->apply(matrix);
}

void Controller::applyPostTransform(glm::mat4 &matrix) {
    this->postTransform->apply(matrix);
}

Controller::Controller(const float& movementSpeed,const float& rotationSpeed) : movementSpeed(movementSpeed), rotationSpeed(rotationSpeed) {
    this->preTransform = std::make_unique<TransformationComposite>();
    this->postTransform = std::make_unique<TransformationComposite>();
    this->translation = new Translation();
    this->rotationX = new Rotation(0,{1,0,0});
    this->rotationY = new Rotation(0,{0,1,0});
    this->rotationZ = new Rotation(0,{0,0,1});

    this->preTransform->addTransformation(this->translation);
    this->postTransform->addTransformation({this->rotationX,this->rotationY,this->rotationZ});

    InputManager::getInstance().getInputMap().addPairing('w',
         [this] (int key) {
             this->translation->translate(glm::vec3{0,0,1} * Application::getInstance().getDeltaTime() * this->movementSpeed);
         }
    );
    InputManager::getInstance().getInputMap().addPairing('s',
         [this] (int key) {
             this->translation->translate(glm::vec3{0,0,-1} * Application::getInstance().getDeltaTime() * this->movementSpeed);
         }
    );

    InputManager::getInstance().getInputMap().addPairing('a',
         [this] (int key) {
             this->translation->translate(glm::vec3{-1,0,0} * Application::getInstance().getDeltaTime() * this->movementSpeed);
         }
    );
    InputManager::getInstance().getInputMap().addPairing('d',
         [this] (int key) {
             this->translation->translate(glm::vec3{1,0,0} * Application::getInstance().getDeltaTime() * this->movementSpeed);
         }
    );

    InputManager::getInstance().getInputMap().addPairing('q',
         [this] (int key) {
             this->translation->translate(glm::vec3{0,1,0} * Application::getInstance().getDeltaTime() * this->movementSpeed);
         }
    );
    InputManager::getInstance().getInputMap().addPairing('e',
         [this] (int key) {
             this->translation->translate(glm::vec3{0,-1,0} * Application::getInstance().getDeltaTime() * this->movementSpeed);
         }
    );
    InputManager::getInstance().getInputMap().addPairing('r',
         [this] (int key) {
             this->rotationY->rotate(this->rotationSpeed * Application::getInstance().getDeltaTime());
         }
    );
    InputManager::getInstance().getInputMap().addPairing('t',
         [this] (int key) {
             this->rotationY->rotate(-this->rotationSpeed * Application::getInstance().getDeltaTime());
         }
    );
}
