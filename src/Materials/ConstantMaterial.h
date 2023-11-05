//
// Created by Tonz on 27.09.2023.
//

#pragma once

#include "Material.h"

class ConstantMaterial : public Material {
public:
    ConstantMaterial(const glm::vec3& objectColor = {1,1,0}) : objectColor(objectColor), Material("shader_constant"){

    }

    virtual void uploadVariables() override;

    [[nodiscard]] const ShaderProgram& getShader() const;

    void setObjectColor(const glm::vec3 &objectColor) override {
        this->objectColor = objectColor;
    }

protected:
    explicit ConstantMaterial(const std::string& programName, const glm::vec3& objectColor) : Material(programName), objectColor(objectColor){}

    glm::vec3 objectColor{1,1,0};
};