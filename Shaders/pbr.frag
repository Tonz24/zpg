#version 420
#include "lights.glsl"

#include "transformBuffer.glsl"

#define PI 3.1415926f

in vec3 worldSpacePos;
in vec3 worldSpaceNormal;
in vec4 lightSpacePos;
in vec2 uv;

uniform float time;

struct Material {
    vec3 albedo;
    float roughness;
    float metallic;
    vec3 emissive;
    float ao;

    int hasAlbedoMap;
    int hasRoughnessMap;
    int hasMetallicMap;
    int hasAoMap;
};

uniform Material material;


layout (binding = 0) uniform sampler2D albedoMap;
layout (binding = 1) uniform sampler2D roughnessMap;
layout (binding = 2) uniform sampler2D metallicMap;
layout (binding = 3) uniform sampler2D aoMap;
layout (binding = 4) uniform sampler2D shadowMap;


out vec4 frag_color;

float calculateShadow(){
    vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float bias = 0.005;
    return projCoords.z - bias > closestDepth ? 1.0 : 0.0;
}
vec3 fresnelSchlick(vec3 F0, vec3 V, vec3 H) {
    return F0 + (vec3(1.0) - F0) * pow(1.0 - max(dot(V,H),0.0), 5.0);
}

float getReflectionCoefficient(float ior1, float ior2){
    return pow((ior1 - ior2) / (ior1 + ior2),2.0);
}

vec3 getHalfway(vec3 v1, vec3 v2){
    return normalize (v1 + v2);
}

float D(vec3 N, vec3 H, float roughness){
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N,H),0.0);
    float NdotH2 = NdotH*NdotH;

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return a2 / denom;
}

//Schlick-Beckmann
float GX(vec3 N, vec3 X, float a){
    float NdotX = max(dot(N,X),0.0001);
    float k = a * 0.5;

    float denom = max(NdotX * (1.0 - k) + k,0.0001);

    return NdotX / denom;
}

//G-Smith
float G(vec3 L, vec3 N, vec3 V, float a){
    return GX(L,N,a) * GX(V,N,a);
}

vec3 calcPBR(vec3 L, vec3 V,vec3 N, vec3 F0, Material mat){
    float VdotN = max(dot(N,V),0.0001);
    float LdotN = max(dot(N,L),0.0001);
    vec3 H = normalize(L + V);
    N = normalize(N);

    float alpha = pow(mat.roughness,2.0);
    vec3 kSpecular = fresnelSchlick(F0,V,H);
    vec3 kDiffuse = vec3(1.0) - kSpecular;
    vec3 lambert = mat.albedo / PI;

    float fCookTorranceDenom = 4.0 * VdotN * LdotN;
    vec3 fCookTorranceNumer = D(N,H,mat.roughness) * G(L,N,V,alpha) * kSpecular;

    vec3 cookTorrance = fCookTorranceNumer / fCookTorranceDenom;

    vec3 BRDF = kDiffuse * lambert + cookTorrance;

    return BRDF;
}

void main() {
    vec3 color = vec3(0);

    vec3 dirToCamera = worldSpaceCameraPos - worldSpacePos;
    vec3 nDirToCamera = normalize(dirToCamera);
    vec3 normal = normalize(worldSpaceNormal);

    Material thisSample;
    thisSample.albedo = mix(material.albedo,texture(albedoMap,uv).xyz,float(material.hasAlbedoMap));
    thisSample.roughness = mix(material.roughness,texture(roughnessMap,uv).x,float(material.hasRoughnessMap));
    thisSample.metallic = mix(material.metallic,texture(metallicMap,uv).x,float(material.hasMetallicMap));
    thisSample.ao = mix(0.0,texture(aoMap,uv).x,float(material.hasAoMap));
    thisSample.emissive = material.emissive;

    //point lights
    for (int i = 0; i < pointLightCount && i < MAX_N_POINT_LIGHTS; i++) {
        PointLight light = pointLights[i];

        vec3 dirToLight = light.worldSpacePos - worldSpacePos; //fragment pos to light pos
        float distToLight = length(dirToLight);
        vec3 nDirToLight = normalize(dirToLight);

        vec3 V = nDirToCamera;
        vec3 L = nDirToLight;

        float attenuation = getAttenuation(light,distToLight);

        vec3 F0 = mix(vec3(0.04), thisSample.albedo, thisSample.metallic);

        color += thisSample.emissive + calcPBR(L,V,normal,F0,thisSample) * light.color * max(dot(L,normal),0.0) * attenuation;
    }
    //dir lights
    for (int i = 0; i < directionalLightCount && i < MAX_N_DIRECTIONAL_LIGHTS; i++) {
        DirectionalLight light = directionalLights[i];

        vec3 dirToLight = light.direction; //fragment pos to light pos
        float distToLight = length(dirToLight);
        vec3 nDirToLight = normalize(dirToLight);

        vec3 V = nDirToCamera;
        vec3 L = nDirToLight;

        vec3 F0 = mix(vec3(0.04), thisSample.albedo, thisSample.metallic);

        color += thisSample.emissive + calcPBR(L,V,normal,F0,thisSample) * light.color * max(dot(L,normal),0.0);
    }

    vec3 ambient = vec3(0.03) * thisSample.albedo * thisSample.ao;
    color += ambient;

    //frag_color = vec4((ambient +  (1 - calculateShadow())* (diffuse + specular))*objectColor,1.0);
    frag_color = vec4(color,1);
}