#version 420

in vec3 col;
in vec2 uv;

out vec4 frag_color;

uniform vec3 color1;
uniform vec3 color2;

void main () {
     vec2 uvCentered = uv*2 - 1;
     float dst = distance(vec2(0), uvCentered);
     frag_color = vec4 (mix(color1,color2,dst), 1.0);
}