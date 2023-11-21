//
// Created by Tonz on 11.11.2023.
//

#include "PBMaterial.h"

PBMaterial::PBMaterial(const glm::vec3 &albedo, float roughness, float metallic)
        : Material("shader_pbr"), albedo(albedo), roughness(roughness), metallic(metallic){}

void PBMaterial::uploadVariables() {
    Material::uploadVariables();
    this->shader.setVar("material.albedo",this->albedo);
    this->shader.setVar("material.roughness",this->roughness);
    this->shader.setVar("material.emissive",this->emissive);
    this->shader.setVar("material.metallic",this->metallic);

    if (this->albedoMap != nullptr){
        this->albedoMap->bind(0);
        this->shader.setVar("material.hasAlbedoMap",1);
    }
    else this->shader.setVar("material.hasAlbedoMap",0);

    if (this->roughnessMap != nullptr){
        this->roughnessMap->bind(1);
        this->shader.setVar("material.hasRoughnessMap",1);
    }
    else this->shader.setVar("material.hasRoughnessMap",0);

    if (this->metallicMap != nullptr){
        this->metallicMap->bind(2);
        this->shader.setVar("material.hasMetallicMap",1);
    }
    else this->shader.setVar("material.hasMetallicMap",0);

    if (this->aoMap != nullptr){
        this->aoMap->bind(3);
        this->shader.setVar("material.hasAoMap",1);
    }
    else this->shader.setVar("material.hasAoMap",0);
}

void PBMaterial::setObjectColor(const glm::vec3 &objectColor) {

}

void PBMaterial::setTextures(std::shared_ptr<Texture> albedoMap, std::shared_ptr<Texture> roughnessMap, std::shared_ptr<Texture> metallicMap, std::shared_ptr<Texture> aoMap) {
    this->albedoMap = std::move(albedoMap);
    this->roughnessMap = std::move(roughnessMap);
    this->metallicMap = std::move(metallicMap);
    this->aoMap = std::move(aoMap);
}
