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

const float weight = 1.0 / 11.0;

void main() {
    vec3 col = vec3(0);

    col += texture(screenTexture,uv + offsets[0]).xyz * weight;
    col += texture(screenTexture,uv + offsets[1]).xyz * weight;
    col += texture(screenTexture,uv + offsets[2]).xyz * weight;
    col += texture(screenTexture,uv + offsets[3]).xyz * weight;
    col += texture(screenTexture,uv + offsets[4]).xyz * weight;
    col += texture(screenTexture,uv + offsets[5]).xyz * weight;
    col += texture(screenTexture,uv + offsets[6]).xyz * weight;
    col += texture(screenTexture,uv + offsets[7]).xyz * weight;
    col += texture(screenTexture,uv + offsets[8]).xyz * weight;
    col += texture(screenTexture,uv + offsets[9]).xyz * weight;
    col += texture(screenTexture,uv + offsets[10]).xyz * weight;

    fragColor = vec4(col,1.0);
}