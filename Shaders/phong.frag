#version 420
#include "lights.glsl"

#include "transformBuffer.glsl"

in vec3 worldSpacePos;
in vec3 worldSpaceNormal;
in vec4 lightSpacePos;
in vec2 uv;

uniform float specularity;
uniform vec3 objectColor;
uniform float ambientFactor;
uniform float diffuseFactor;
uniform float specularFactor;
uniform float time;
uniform int hasDiffuse;
uniform int hasSpecular;

uniform sampler2D shadowMap;

layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2D specularMap;

out vec4 frag_color;

float getAttenuation(PointLight light, float dist){
    return 1.0 / (light.kConstant + light.kLinear * dist + light.kQuadratic * pow(dist,2.0));
}
float getAttenuationSpotLight(SpotLight light, float dist){
    return 1.0 / (light.kConstant + light.kLinear * dist + light.kQuadratic * pow(dist,2.0));
}

float calculateShadow(){
    vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float bias = 0.005;
    return projCoords.z - bias > closestDepth ? 1.0 : 0.0;
}

void main() {
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    vec3 ambient = vec3(0);

    vec3 dirToCamera = worldSpaceCameraPos - worldSpacePos;
    vec3 nDirToCamera = normalize(dirToCamera);
    vec3 nNormal = normalize(worldSpaceNormal);

    vec3 diffuseColor = mix(objectColor,texture(diffuseMap,uv).xyz,float(hasDiffuse));
    vec3 specularComponent = mix(vec3(1.0),texture(specularMap,uv).xyz,float(hasSpecular));

    //point lights
    for (int i = 0; i < pointLightCount && i < MAX_N_POINT_LIGHTS; i++) {
        PointLight light = pointLights[i];

        vec3 dirToLight = light.worldSpacePos - worldSpacePos; //fragment pos to light pos
        float distToLight = length(dirToLight);
        vec3 nDirToLight = normalize(dirToLight);

        float attenuation = getAttenuation(light,distToLight);

        vec3 thisAmbient = light.color * ambientFactor;
        ambient += thisAmbient * attenuation;


        float diffuseDot = dot(nNormal,nDirToLight);
        float lightIntensity = max(diffuseDot,0.0);
        vec3 thisDiffuse = lightIntensity * light.color * diffuseFactor;
        diffuse += thisDiffuse * attenuation;

        if (diffuseDot >= 0.0) {
            float specularIntensity = pow(max(dot(reflect(-nDirToLight, nNormal), nDirToCamera), 0.0), specularity);
            vec3 thisSpecular = light.color * specularIntensity * specularFactor * specularComponent;
            specular += thisSpecular * attenuation;
        }
    }
    //spotlights
    for (int i = 0; i < spotLightCount && i < MAX_N_SPOT_LIGHTS; i++) {
        SpotLight light = spotLights[i];

        vec3 dirToLight = light.worldSpacePos - worldSpacePos; //fragment pos to light pos
        float distToLight = length(dirToLight);
        vec3 nDirToLight = normalize(dirToLight);
        float attenuation = getAttenuationSpotLight(light,distToLight);
        vec3 nLightDir = normalize(light.direction);

        float theta = dot(nDirToLight, normalize(-light.direction));
        float epsilon = (light.innerCutoffAngle - light.outerCutoffAngle);
        float intensity = clamp((theta - light.outerCutoffAngle) / epsilon, 0.0, 1.0);

        float diffuseDot = dot(nNormal,nDirToLight);
        float lightIntensity = max(diffuseDot,0.0);
        vec3 thisDiffuse = lightIntensity * light.color * diffuseFactor;
        diffuse += thisDiffuse * attenuation * intensity;

        if (diffuseDot >= 0.0) {
            vec3 reflectDir = reflect(-nDirToLight, nNormal);
            float specularIntensity = pow(max(dot(reflectDir, nDirToCamera), 0.0), specularity);
            vec3 thisSpecular = light.color * specularIntensity * specularFactor * intensity * specularComponent;
            specular += thisSpecular * attenuation;
        }
    }
    for (int i = 0; i < directionalLightCount && i < MAX_N_DIRECTIONAL_LIGHTS; i++) {
        DirectionalLight light = directionalLights[i];

        vec3 nLightDir = normalize(light.direction);

        float diffuseDot = dot(nNormal,nLightDir);
        float lightIntensity = max(diffuseDot,0.0);
        vec3 thisDiffuse = lightIntensity * light.color * diffuseFactor;
        diffuse += thisDiffuse;

        if (diffuseDot >= 0.0) {
            vec3 reflectDir = reflect(-nLightDir, nNormal);
            float specularIntensity = pow(max(dot(reflectDir, nDirToCamera), 0.0), specularity);
            vec3 thisSpecular = light.color * specularIntensity * specularFactor * specularComponent;
            specular += thisSpecular;
        }
    }

    //frag_color = vec4((ambient +  (1 - calculateShadow())* (diffuse + specular))*objectColor,1.0);
    frag_color = vec4((ambient +  diffuse + specular)*diffuseColor,1.0);
}