//
// Created by Tonz on 03.10.2023.
//

#include "Renderable.h"

void Renderable::draw() {
    this->material->uploadVariables();
    this->transform.uploadToGpu();
    this->model->draw();
}
