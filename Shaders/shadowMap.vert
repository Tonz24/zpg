#version 420

#include "transformBuffer.glsl"
#include "lights.glsl"

layout (location=0) in vec3 vp;

void main() {
    gl_Position = projMat * viewMat * modelMat * vec4(vp,1.0);
}