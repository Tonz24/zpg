//
// Created by Tonz on 16.10.2023.
//

#include "BlinnMaterial.h"

BlinnMaterial::BlinnMaterial(const glm::vec3 &objectColor, const float &specularity, const float &ambientFactor,
                             const float &specularFactor) : PhongMaterial(objectColor, specularity, ambientFactor,
                                                                          specularFactor) {
    this->shader = Shader::getShaderProgram("shader_blinn");
}
