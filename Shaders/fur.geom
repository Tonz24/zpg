#version 420
layout (triangles) in;
layout (triangle_strip, max_vertices = 146) out;
layout(invocations = 10) in;

in VS_OUT{
    vec4 clipSpaceNormal;
    vec2 uv;
} gs_in[];

out GS_OUT{
    vec2 uv;
    flat int layer;
} gs_out;

uniform int layerCount;
uniform float layerOffset;
void main() {

    vec4 wSpaceNormal = gs_in[0].clipSpaceNormal;
    vec4 wSpaceNormal1 = gs_in[1].clipSpaceNormal;
    vec4 wSpaceNormal2 = gs_in[2].clipSpaceNormal;

    int maxLayers = 144 / 6; //6 vertices per layer

    for (int i = 0; i < layerCount  - (gl_InvocationID * 24); i++){
        int layer = gl_InvocationID * maxLayers + i;
        gl_Position = gl_in[0].gl_Position + wSpaceNormal * layer * layerOffset;
        gs_out.uv = gs_in[0].uv;
        gs_out.layer = layer;
        EmitVertex();
        gl_Position = gl_in[1].gl_Position + wSpaceNormal1 * layer * layerOffset;
        gs_out.uv = gs_in[1].uv;
        gs_out.layer = layer;
        EmitVertex();
        gl_Position = gl_in[2].gl_Position + wSpaceNormal2 * layer * layerOffset;
        gs_out.uv = gs_in[2].uv;
        gs_out.layer = layer;
        EmitVertex();
        EndPrimitive();
    }
}