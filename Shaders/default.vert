#version 420
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 colIn;
layout(location=3) in vec2 uvIn;

#include "Tonda.glsl"

out vec3 col;
out vec3 worldSpacePos;
out vec3 worldSpaceNormal;
out vec2 uv;

uniform float time;

layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
    vec3 worldSpaceCameraPos;
};

void main () {
    col = normal * colIn;
    uv = uvIn;

    vec4 wSpacePos = modelMat * vec4(vp,1.0);
    worldSpacePos = wSpacePos.xyz;

    vec4 wNormal = modelMat * vec4(normal,0.0);
    worldSpaceNormal = wNormal.xyz;

    gl_Position = projMat * viewMat * wSpacePos;
}