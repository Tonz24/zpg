//
// Created by Tonz on 16.10.2023.
//

#include "BlinnMaterial.h"

BlinnMaterial::BlinnMaterial(const glm::vec3& objectColor, const float& diffuseFactor,const float& ambientFactor,
         const float& specularity, const float& specularFactor) : PhongMaterial(objectColor, diffuseFactor, ambientFactor,
                                                                                specularity,specularFactor) {
    this->shader = Shader::getShaderProgram("shader_blinn");
}
