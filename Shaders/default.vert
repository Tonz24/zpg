#version 420
layout(location=0) in vec3 vp;
layout(location=1) in vec3 colIn;
layout(location=2) in vec2 uvIn;

out vec3 col;
out vec2 uv;

uniform float time;

layout (std140, binding = 5) uniform Transform{
    vec3 translation;
    vec3 rotation;
    vec3 scale;

    mat4x4 modelMat;
};

vec3 rotate(vec3 vector, float angle){
    vec2 result = mat2(cos(angle),-sin(angle), sin(angle),cos(angle)) * vector.xy;
    return vec3(result.xy,0);
}

void main () {
    col = colIn;
    uv = uvIn;
    gl_Position = modelMat * vec4(vp, 1.0);
}