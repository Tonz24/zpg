#version 420

in vec3 col;
in vec2 uv;
out vec4 frag_color;

uniform vec3 objectColor;

void main () {
     frag_color = vec4 (objectColor, 1.0);
}