
layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
    mat4x4 normalMatrix;
    vec3 worldSpaceCameraPos;
};