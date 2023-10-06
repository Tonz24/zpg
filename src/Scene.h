//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include<vector>
#include <memory>


#include "Renderable.h"
#include <GLFW/glfw3.h>
class Scene {
public:
    void addModel(Renderable& model);

    void draw();

private:
    std::vector<std::unique_ptr<Renderable>> models;
};


