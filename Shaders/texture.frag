#version 420

in vec3 col;
in vec2 uv;

out vec4 frag_color;

uniform vec3 color1;
uniform vec3 color2;

uniform sampler2D tex;

void main () {
     frag_color = texture(tex, uv);
}