#version 420

uniform float time;
uniform mat4 lightspaceMat;

layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 colIn;
layout(location=3) in vec2 uvIn;

#include "transformBuffer.glsl"
//out vec4 lightSpacePos;

uniform float offset;

out VS_OUT{
    vec4 clipSpaceNormal;
    vec2 uv;
} vs_out;

void main () {
    vs_out.uv = uvIn;
    mat4 vpMat = projMat * viewMat;
    //lightSpacePos = lightspaceMat * wSpacePos;
    vec3 n = mat3(normalMatrix) * normal;
    vs_out.clipSpaceNormal = vpMat * vec4(n,0);
    gl_Position = vpMat * modelMat * vec4(vp,1.0);
}