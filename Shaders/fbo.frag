#version 420
out vec4 fragColor;

in vec2 uv;

uniform sampler2D screenTexture;

uniform float time;
uniform vec3 filter;

const float offset = 1.0 / 1000.0;

//https://github.com/dmnsgn/glsl-tone-map
vec3 reinhard2(vec3 x) {
    const float L_white = 4.0;

    return (x * (1.0 + x / (L_white * L_white))) / (1.0 + x);
}

void main() {
    vec3 col = texture(screenTexture,uv).xyz;
    fragColor = vec4(col.x, col.y + 0.1, col.z,1.0);
}