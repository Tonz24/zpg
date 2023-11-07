#version 420
layout (location = 0) in vec3 vp;


out SKYBOX_OUT {
    vec3 uv;
} vs_out;

#include "transformBuffer.glsl"
void main() {
    vs_out.uv = vp;
    vec4 pos = projMat * mat4(mat3(viewMat)) * vec4(vp, 1.0);
    gl_Position = pos.xyww;
}