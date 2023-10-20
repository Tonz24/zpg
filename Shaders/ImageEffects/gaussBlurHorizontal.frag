#version 420
in vec2 uv;

uniform sampler2D screenTexture;
uniform float time;

out vec4 fragColor;

const float scale = 1.0 / 1000.0;

const vec2 offsets[11] = {
    vec2(-scale*5,0), vec2(-scale*4,0),vec2(-scale*3,0), vec2(-scale*2,0), vec2(-scale,0),
                                vec2(0,0),
    vec2(scale,0), vec2(scale*2,0),vec2(scale*3,0), vec2(scale*4,0), vec2(scale*5,0)
};

void main() {
    vec3 col = vec3(0);

    col += texture(screenTexture,uv + offsets[0]).xyz * 0.0093;
    col += texture(screenTexture,uv + offsets[1]).xyz * 0.028002;
    col += texture(screenTexture,uv + offsets[2]).xyz * 0.065984;
    col += texture(screenTexture,uv + offsets[3]).xyz * 0.121703;
    col += texture(screenTexture,uv + offsets[4]).xyz * 0.175713;
    col += texture(screenTexture,uv + offsets[5]).xyz * 0.198596;
    col += texture(screenTexture,uv + offsets[6]).xyz * 0.175713;
    col += texture(screenTexture,uv + offsets[7]).xyz * 0.121703;
    col += texture(screenTexture,uv + offsets[8]).xyz * 0.065984;
    col += texture(screenTexture,uv + offsets[9]).xyz * 0.028002;
    col += texture(screenTexture,uv + offsets[10]).xyz * 0.0093;

    fragColor = vec4(col,1.0);
}