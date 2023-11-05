#version 420
in vec2 uv;

uniform sampler2D screenTexture;
out vec4 fragColor;

void main() {
    vec3 col = texture(screenTexture,uv).xyz;
    fragColor = vec4(col,1.0);
}