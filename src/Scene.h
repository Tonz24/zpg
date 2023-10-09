//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include<vector>
#include <memory>


#include "Renderable.h"
#include "Camera.h"

class Scene {
public:
    void addModel(Renderable& model);

    void draw();

    Camera cam;

private:
    std::vector<std::unique_ptr<Renderable>> models;
};


