#version 420
out vec4 fragColor;

in vec2 uv;

uniform sampler2D screenTexture;

uniform float time;

void main() {
    vec3 texColor = texture(screenTexture, uv).xyz;

    fragColor = vec4(   sin(texColor.x *sin(time)*50) *0.5 + 0.5 , sin(texColor.y* cos(time)*50 + 1.47) *0.5 + 0.5 , texColor.z,1.0);
}