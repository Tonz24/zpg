#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 colIn;
layout(location=2) in vec2 uvIn;

out vec3 col;
out vec2 uv;

uniform vec3 translation;
uniform float time;

vec3 rotate(vec3 vector, float angle){
    vec2 result = mat2(cos(angle),-sin(angle), sin(angle),cos(angle)) * vector.xy;
    return vec3(result.xy,0);
}

void main () {
    col = colIn;
    uv = uvIn;
    gl_Position = vec4(vp + translation, 1.0);
}