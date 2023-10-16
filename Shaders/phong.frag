#version 420

#define MAX_N_LIGHTS 100

in vec3 worldSpacePos;
in vec3 worldSpaceNormal;
in vec2 uv;

uniform float specularity;
uniform vec3 objectColor;
uniform float ambientFactor;
uniform float specularFactor;

struct Light{
    vec3 color;
    float kConstant; // 16 B

    vec3 worldSpacePos;
    float kLinear; // 32 B

    float kQuadratic; // 48 B
};

layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
    vec3 worldSpaceCameraPos;
};

layout (std140, binding = 6) uniform Lights{
    Light lights[MAX_N_LIGHTS]; // 100 * 48 B

    vec3 ambientColor;
    int lightCount; // 100 * 48 B + 16 B
};

uniform float time;

out vec4 frag_color;

float getAttenuation(Light light, float dist){
    return 1.0 / (light.kConstant + light.kLinear * dist + light.kQuadratic * pow(dist,2.0));
}

void main() {

    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    vec3 ambient = vec3(0);

    vec3 dirToCamera = worldSpaceCameraPos - worldSpacePos;
    vec3 nDirToCamera = normalize(dirToCamera);
    vec3 nNormal = normalize(worldSpaceNormal);

    for (int i = 0; i < lightCount && i < MAX_N_LIGHTS; i++) {
        Light light = lights[i];

        vec3 dirToLight = light.worldSpacePos - worldSpacePos; //fragment pos to light pos
        float distToLight = length(dirToLight);
        vec3 nDirToLight = normalize(dirToLight);

        float attenuation = getAttenuation(light,distToLight);

        vec3 thisAmbient = light.color * ambientFactor;
        ambient += thisAmbient * attenuation;

        float lightIntensity = max(dot(nNormal,nDirToLight),0.0);
        vec3 thisDiffuse = lightIntensity * light.color;
        diffuse += thisDiffuse * attenuation;

        float nDotL = dot(nNormal,nDirToLight);
        if (nDotL > 0.0) {
            float specularIntensity = pow(max(dot(reflect(-nDirToLight, nNormal), nDirToCamera), 0.0), specularity);
            vec3 thisSpecular = light.color * specularIntensity * specularFactor;
            specular += thisSpecular * attenuation;
        }
    }
    frag_color = vec4(clamp((specular + diffuse + ambient)*objectColor,0.0,1.0),1.0);
}