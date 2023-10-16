#version 420

#define MAX_N_LIGHTS 100

in vec3 worldSpacePos;
in vec3 worldSpaceNormal;
in vec2 uv;

const vec3 ambient = vec3(0);

uniform float specularity;
uniform vec3 objectColor;

struct Light{
    vec3 color;
    vec3 worldSpacePos;
};

layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
    vec3 worldSpaceCameraPos;
};

layout (std140, binding = 6) uniform Lights{
    Light lights[MAX_N_LIGHTS];
    vec3 ambientColor;
    int lightCount;
};

uniform float time;

out vec4 frag_color;
void main() {


    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    vec3 dirToCamera = worldSpaceCameraPos - worldSpacePos;
    vec3 nDirToCamera = normalize(dirToCamera);
    vec3 nNormal = normalize(worldSpaceNormal);

    for (int i = 0; i < lightCount && i < MAX_N_LIGHTS; i++) {
        Light light = lights[i];

        vec3 dirToLight = light.worldSpacePos - worldSpacePos; //fragment pos to light pos
        vec3 nDirToLight = normalize(dirToLight);

        float lightIntensity = max(dot(nNormal,nDirToLight),0.0);
        diffuse += lightIntensity * light.color;

        float nDotL = dot(nNormal,nDirToLight);
        if (nDotL  > 0.0) {
            float specularIntensity = pow(max(dot(reflect(-nDirToLight, nNormal), nDirToCamera), 0.0), specularity);
            specular += light.color * specularIntensity * 5;
        }
    }
    frag_color = vec4(clamp((specular + diffuse + ambient)*objectColor,0.0,1.0),1.0);
}