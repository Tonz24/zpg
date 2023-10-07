#version 420

in vec3 col;
in vec2 uv;

out vec4 frag_color;

void main () {
     frag_color = vec4 (col*0.5 + 0.5, 1.0);
}