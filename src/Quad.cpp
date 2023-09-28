//
// Created by Tonz on 26.09.2023.
//

#include "Quad.h"

Quad::Quad(Material& material) : Model(quadData,material){
}

Quad::Quad(glm::vec3 translation, Material& material) : Model(quadData,material,translation) {
}
