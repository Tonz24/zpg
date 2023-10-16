//
// Created by Tonz on 10.10.2023.
//

#pragma once


#include "Renderable.h"

class Light : public Renderable {
public:
    Light(Model* model = new Cube(), Material* m = new Material(), TransformationComposite* transformation = new TransformationComposite());
    glm::vec3 color;
    

    void uploadLightData();
};