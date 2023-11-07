//
// Created by Tonz on 16.10.2023.
//

#pragma once

#include "LambertMaterial.h"

class PhongMaterial : public LambertMaterial {
public:
    explicit PhongMaterial(const glm::vec3& objectColor = {1,1,0}, const float& diffuseFactor = 1,const float& ambientFactor = 0.1,
                  const float& specularity = 32, const float& specularFactor = 1) :
            LambertMaterial("shader_phong",objectColor,diffuseFactor,ambientFactor),specularity(specularity), specularFactor(specularFactor) {}

    void uploadVariables() override;

    void setSpecularity(float specularity);
    void setSpecularFactor(float specularFactor);

    void setSpecularMap(std::shared_ptr<Texture> specularMap);

protected:
    explicit PhongMaterial(const std::string& programName ,const glm::vec3& objectColor = {1,1,0}, const float& diffuseFactor = 1,const float& ambientFactor = 0.1,
                  const float& specularity = 32, const float& specularFactor = 1) :
            LambertMaterial(programName,objectColor,diffuseFactor,ambientFactor),specularity(specularity), specularFactor(specularFactor) {}

    float specularity{32};
    float specularFactor{1};


    std::shared_ptr<Texture> specularMap;
};