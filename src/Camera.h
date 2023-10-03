//
// Created by Tonz on 02.10.2023.
//

#pragma once
#include "iostream"

#include "glm.hpp"
#include "InputManager.h"


class Camera {
public:

    void moveForward(int key){
        pos.x += 1;
        std::cout << "test pozice: " << pos.x << " " << pos.y << std::endl;
    }

    void moveBack(int key){
        pos.x -= 1;
        std::cout << "test pozice: " << pos.x << " " << pos.y << std::endl;
    }

    void moveRight(int key){
        pos.y += 1;
        std::cout << "test pozice: " << pos.x << " " << pos.y << std::endl;
    }

    void moveLeft(int key){
        pos.y -= 1;
        std::cout << "test pozice: " << pos.x << " " << pos.y << std::endl;
    }

    Camera(){
        std::function<void(int)> f = [this] (int key) { moveForward(key); };
        std::function<void(int)> b = [this] (int key) { moveBack(key); };
        std::function<void(int)> r = [this] (int key) { moveRight(key); };
        std::function<void(int)> l = [this] (int key) { moveLeft(key); };

        InputManager::getInstance().getInputMap().addPairing('w',f);
        InputManager::getInstance().getInputMap().addPairing('s',b);
        InputManager::getInstance().getInputMap().addPairing('a',l);
        InputManager::getInstance().getInputMap().addPairing('d',r);
    }

private:
    glm::vec2 pos{};
};


