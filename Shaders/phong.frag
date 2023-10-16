#version 420

in vec3 worldSpacePos;
in vec3 worldSpaceNormal;
in vec2 uv;

const vec3 lightColor = vec3(0.557,0.63,0.3);
const vec3 ambient = vec3(0.337,0.127,0.035);

uniform float specularity;
uniform vec3 objectColor;

struct Light{
    vec3 worldSpacePos;
    vec3 color;
};

layout (std140, binding = 6) uniform Lights{
    Light lights[100];
    int lightCount;
    vec3 ambientColor;
};

layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
    vec3 worldSpaceCameraPos;
};

uniform float time;

out vec4 frag_color;
void main() {

    vec3 lightPos = vec3(0,sin(time)*5,cos(time)*5);

    vec3 dirToLight = lightPos - worldSpacePos; //fragment pos to light pos
    vec3 dirToCamera = worldSpaceCameraPos - worldSpacePos;

    vec3 nDirToLight = normalize(dirToLight);
    vec3 nNormal = normalize(worldSpaceNormal);
    vec3 nDirToCamera = normalize(dirToCamera);

    float lightIntensity = max(dot(nNormal,nDirToLight),0.0);
    vec3 diffuse = lightIntensity * lightColor;

    float specularIntensity = pow(max(dot(reflect(-nDirToLight,nNormal),nDirToCamera),0.0),specularity);
    vec3 specular = lightColor * specularIntensity * 5;

    frag_color = vec4(clamp((specular + diffuse + ambient)*objectColor,0.0,1.0),1.0);
}