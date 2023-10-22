#define MAX_N_POINT_LIGHTS 30
#define MAX_N_SPOT_LIGHTS 30

struct PointLight{
    vec3 color;
    float kConstant; // 16 B

    vec3 worldSpacePos;
    float kLinear; // 32 B

    float kQuadratic; // 48 B
};

struct SpotLight{
    vec3 color;
    float kConstant; // 16 B

    vec3 worldSpacePos;
    float kLinear; // 32 B

    vec3 direction;
    float kQuadratic; // 48 B

    float cutoffAngle; // 64 B
};

layout (std140, binding = 5) uniform Transform{
    mat4x4 modelMat;
    mat4x4 viewMat;
    mat4x4 projMat;
    vec3 worldSpaceCameraPos;
};

layout (std140, binding = 6) uniform Lights{
    PointLight pointLights[MAX_N_POINT_LIGHTS]; // 100 * 48 B
    SpotLight spotLights[MAX_N_SPOT_LIGHTS]; // 100 * 48 B + 100 * 64 B

    int pointLightCount; // 100 * 48 B + 16 B
    int spotLightCount; // 100 * 48 B + 16 B
};