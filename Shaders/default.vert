#version 420
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 colIn;
layout(location=3) in vec2 uvIn;

#include "transformBuffer.glsl"

out vec3 col;
out vec3 worldSpacePos;
out vec3 worldSpaceNormal;
out vec2 uv;

uniform float time;

void main () {
    col = normal * colIn;
    uv = uvIn;

    vec4 wSpacePos = modelMat * vec4(vp,1.0);
    worldSpacePos = wSpacePos.xyz;

    worldSpaceNormal = mat3(normalMatrix) * normal;

    gl_Position = projMat * viewMat * wSpacePos;
}