#version 420

in SKYBOX_OUT {
    vec3 uv;
} fs_in;

uniform samplerCube skybox;

out vec4 fragColor;
void main() {
    fragColor = texture(skybox, fs_in.uv);
}