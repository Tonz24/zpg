#version 420
in vec2 uv;

uniform sampler2D screenTexture;
uniform float time;
uniform int tonemapType;

out vec4 fragColor;

//https://github.com/dmnsgn/glsl-tone-map
vec3 aces(vec3 x) {
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

vec3 filmic(vec3 x) {
    vec3 X = max(vec3(0.0), x - 0.004);
    vec3 result = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);
    return pow(result, vec3(2.2));
}

vec3 reinhard(vec3 x) {
    return x / (1.0 + x);
}

void main() {
    vec3 col = texture(screenTexture,uv).xyz;
    switch (tonemapType){
        case 0:
            col = aces(col);
            break;

        case 1:
            col = filmic(col);
            break;

        case 2:
            col = reinhard(col);
            break;

        default:
            break;
    }
    fragColor = vec4(col,1.0);
}