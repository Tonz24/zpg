#version 420

in vec2 uv;

uniform sampler2D screenTexture;
uniform int sampleCount;
uniform float rcpSampleCount;

uniform float density;
uniform float exposure;
uniform float decay;
uniform float weight;

uniform float radius;
uniform float strength;

uniform vec2 centers[15];

uniform int centerCount;
uniform float rcpCenterCount;

out vec4 fragColor;

vec4 applyRadialBlur(vec2 center){
    vec4 colorSum = texture(screenTexture,uv);
    vec2 dist = uv - center;
    vec2 delta = dist * rcpSampleCount* density;
    vec2 texCoord = uv;
    float thisDecay = 1.0;
    for (int i = 0; i < sampleCount; i++) {
        texCoord -= delta;
        vec4 currentSample = texture(screenTexture,texCoord);
        currentSample *= decay * weight;
        colorSum += currentSample;

        thisDecay *= decay;
    }
    return colorSum * rcpSampleCount * exposure;
}

void main() {
    vec4 colorSum = texture(screenTexture,uv);
    for (int i = 0; i < centerCount; i++) {
       colorSum += applyRadialBlur(centers[i].xy);
    }
    fragColor = colorSum * rcpCenterCount;
}