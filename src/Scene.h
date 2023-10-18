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
    void addModel(const std::shared_ptr<IDrawable>& drawable);
    void addTickable(const std::shared_ptr<ITickable>& tickable);

    void draw();

    void setCamera(const std::shared_ptr<Camera>& newCamera);

private:
    std::shared_ptr<Camera> activeCamera;
    std::vector<std::shared_ptr<IDrawable>> models;
    std::vector<std::shared_ptr<ITickable>> tickables;
};