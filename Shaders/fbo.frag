#version 420
out vec4 fragColor;

in vec2 uv;

uniform sampler2D screenTexture;

void main() {
    vec3 texColor = texture(screenTexture, uv).xyz;
    fragColor = vec4(texColor.x - uv.x, texColor.y - uv.y, uv.y * uv.x,1.0);
}