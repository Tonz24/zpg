#version 420

in vec3 col;
in vec2 uv;

out vec4 frag_color;

uniform float time;
uniform sampler2D tex;

void main () {
     frag_color = texture(tex,uv);
}