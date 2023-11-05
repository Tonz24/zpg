#define MAX_N_POINT_LIGHTS 30
#define MAX_N_SPOT_LIGHTS 30
#define MAX_N_DIRECTIONAL_LIGHTS 30

struct PointLight{ //48 B SIZE
    vec3 color;
    float kConstant; // 16 B

    vec3 worldSpacePos;
    float kLinear; // 32 B

    float kQuadratic; // 48 B
};

struct SpotLight{ //64 B SIZE
    vec3 color;
    float kConstant; // 16 B

    vec3 worldSpacePos;
    float kLinear; // 32 B

    vec3 direction;
    float kQuadratic; // 48 B

    float innerCutoffAngle;
    float outerCutoffAngle; // 64 B
};

struct DirectionalLight{ // 48 B SIZE
    vec3 color;
    float kConstant; // 16 B

    vec3 direction;
    float kLinear; // 32 B

    float kQuadratic; // 48 B
};

layout (std140, binding = 6) uniform Lights{
    PointLight pointLights[MAX_N_POINT_LIGHTS]; // 30 * 48 B SIZE
    SpotLight spotLights[MAX_N_SPOT_LIGHTS]; // 30 * 48 B + 30 * 64 B SIZE
    DirectionalLight directionalLights[MAX_N_DIRECTIONAL_LIGHTS]; //  30*48 B + 30*64 + 30*48 B SIZE

    int pointLightCount; // 30*48  + 30*64 + 30*48 B offset
    int spotLightCount; // 30*48  + 30*64 + 30*48  + 16 B offset
    int directionalLightCount; // 30*48  + 30*64 + 30*48  + 32 B offset
};

