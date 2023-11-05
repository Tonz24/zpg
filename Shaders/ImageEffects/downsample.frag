//https://learnopengl.com/Guest-Articles/2022/Phys.-Based-Bloom
//https://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare

#version 420
in vec2 uv;

uniform sampler2D srcTexture;
uniform float bloomTreshold;
uniform int doPrefilter;

out vec3 downsample;

//https://catlikecoding.com/unity/tutorials/advanced-rendering/bloom/
vec3 prefilter(vec3 color){
    float brightness = max(color.r, max(color.g, color.b));
    float contribution = max(0.0, brightness - bloomTreshold);
    contribution /= max(brightness, 0.00001);
    return color * contribution;
}

void main() {
    vec2 texCoords = uv;

    vec2 srcTexelSize = 1.0 / textureSize(srcTexture,0)*2.0;
    float x = srcTexelSize.x;
    float y = srcTexelSize.y;

    vec3 a = texture(srcTexture, vec2(texCoords.x - 2*x, texCoords.y + 2*y)).rgb;
    vec3 b = texture(srcTexture, vec2(texCoords.x,       texCoords.y + 2*y)).rgb;
    vec3 c = texture(srcTexture, vec2(texCoords.x + 2*x, texCoords.y + 2*y)).rgb;

    vec3 d = texture(srcTexture, vec2(texCoords.x - 2*x, texCoords.y)).rgb;
    vec3 e = texture(srcTexture, vec2(texCoords.x,       texCoords.y)).rgb;
    vec3 f = texture(srcTexture, vec2(texCoords.x + 2*x, texCoords.y)).rgb;

    vec3 g = texture(srcTexture, vec2(texCoords.x - 2*x, texCoords.y - 2*y)).rgb;
    vec3 h = texture(srcTexture, vec2(texCoords.x,       texCoords.y - 2*y)).rgb;
    vec3 i = texture(srcTexture, vec2(texCoords.x + 2*x, texCoords.y - 2*y)).rgb;

    vec3 j = texture(srcTexture, vec2(texCoords.x - x, texCoords.y + y)).rgb;
    vec3 k = texture(srcTexture, vec2(texCoords.x + x, texCoords.y + y)).rgb;
    vec3 l = texture(srcTexture, vec2(texCoords.x - x, texCoords.y - y)).rgb;
    vec3 m = texture(srcTexture, vec2(texCoords.x + x, texCoords.y - y)).rgb;

    downsample = e*0.125;
    downsample += (a+c+g+i)*0.03125;
    downsample += (b+d+f+h)*0.0625;
    downsample += (j+k+l+m)*0.125;

    if (doPrefilter == 1){
        downsample = prefilter(downsample);
    }
}