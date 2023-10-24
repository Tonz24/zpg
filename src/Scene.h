//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include<vector>
#include <memory>

#include "Renderable.h"
#include "Camera.h"
#include "Lights/Light.h"

class Scene {
public:
    void addModel(const std::shared_ptr<IDrawable>& drawable);
    void addModel(const std::shared_ptr<Light>& light);
    void addTickable(const std::shared_ptr<ITickable>& tickable);

    void draw();
    void deactivateLights();
    void activateLights();

    void setActiveCamera(const std::shared_ptr<Camera> &activeCamera);

private:
    std::vector<std::shared_ptr<IDrawable>> models;
    std::vector<std::shared_ptr<ITickable>> tickables;
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> activeCamera;
};