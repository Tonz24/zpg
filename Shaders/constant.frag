#version 420

in vec3 col;
in vec2 uv;
out vec4 frag_color;

uniform vec3 color;

void main () {
     frag_color = vec4 (color, 1.0);
}