#version 420
layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 uvIn;

out vec2 uv;

void main() {
    gl_Position = vec4(vp.x, vp.y, 0.0, 1.0);
    uv = uvIn;
}