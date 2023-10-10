#version 420
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 colIn;
layout(location=3) in vec2 uvIn;

out vec3 col;
out vec2 uv;

uniform float time;

struct lightData{
    vec3 pos;
    vec3 color;
    float strength;
};

layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
};

layout(std140, binding = 6) uniform LightData{
    lightData[100] lights;
    int lightsUsed;
};

void main () {
    col = normal * colIn;
    uv = uvIn;
    gl_Position = projMat * viewMat * modelMat * vec4(vp, 1.0);
}