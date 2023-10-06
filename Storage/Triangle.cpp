//
// Created by Tonz on 26.09.2023.
//
#include "Triangle.h"

Triangle::Triangle(Material& material) : Model(triangleData,material) {
}

Triangle::Triangle(glm::vec3 translation, Material& material) : Model(triangleData,material, translation) {
}