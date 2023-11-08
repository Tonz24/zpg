#version 420

in vec2 uv;

out vec4 fragColor;

layout (binding = 0) uniform sampler2D tex1;
layout (binding = 1) uniform sampler2D tex2;

void main() {
    fragColor = texture(tex1,uv) + texture(tex2,uv);
}