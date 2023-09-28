//
// Created by Tonz on 26.09.2023.
//

#pragma once

#include<vector>
#include <memory>

#include "Model.h"
class Scene {
public:
    void addModel(Model& model);

    void draw();

private:
    std::vector<std::unique_ptr<Model>> models;
};


