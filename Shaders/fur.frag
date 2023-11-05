#version 420

uniform vec2 gridDimensions;

out vec4 fragColor;

in GS_OUT{
    vec2 uv;
    flat int layer;
} fs_in;

uniform int layerCount;
uniform float time;

uniform sampler2D noiseTexture;

float hash(uint state){
    state = state * 747796405 + 2891336453;
    uint result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
    result = (result >> 22) ^ result;
    return result / 4294967295.0;
}

void main() {
    vec2 cellCoords = floor(fs_in.uv * gridDimensions) / gridDimensions;

    vec2 perCellCoords = fract(fs_in.uv * gridDimensions) * 2 - 1;
    float dist = length(perCellCoords);
    dist = pow(dist,5.0);

    float normalizedLayer = float(fs_in.layer) / float(layerCount);

    if (normalizedLayer + dist >= texture(noiseTexture,cellCoords).x)
        discard;

    fragColor = vec4(vec3(1.0)*normalizedLayer,1);
}