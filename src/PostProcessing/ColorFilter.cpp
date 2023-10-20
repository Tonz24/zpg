//
// Created by Tonz on 19.10.2023.
//

#include "ColorFilter.h"

ColorFilter::ColorFilter(const glm::vec3& filter) : ImageEffect("effect_filter"), filter(filter) {
}

void ColorFilter::uploadValues() {
    ImageEffect::uploadValues();
    this->shader->setVec3f("filter",this->filter);
}


