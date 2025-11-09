#version 460 core

#define MAX_LIGHTS  5
#define POINT       0
#define DIRECTIONAL 1
#define SPOT        2

in VS_OUT
{
    vec2 texcoord;
    vec3 position;
    vec3 normal;
} fs_in;

out vec4 f_color;

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float range;
    float innerCutoff;
    float outerCutoff;
};

struct Material {
    sampler2D baseMap;
    vec3 baseColor;
    float shininess;
    vec2 tiling;
    vec2 offset;
};

uniform Light u_lights[MAX_LIGHTS];
uniform int u_numLights;
uniform Material u_material;
uniform vec3 u_ambient_light;

float calculateAttentuation(float light_distance, float range)
{
    float attenuation = max(0.0, (1.0 - (light_distance / range)));
    return attenuation * attenuation;
}

vec3 calculateLight(in Light light, in vec3 position, in vec3 normal)
{
    vec3 light_dir;
    float attenuation = 1.0;
    float light_distance;

    switch (light.type)
    {
        case POINT:
            light_dir = normalize(light.position - position);
            light_distance = length(light.position - position);
            attenuation = calculateAttentuation(light_distance, light.range);
        break;

        case DIRECTIONAL:
            light_dir = normalize(light.direction);
        break;

        case SPOT:
            light_dir = normalize(light.position - position);
            light_distance = length(light.position - position);
            attenuation = calculateAttentuation(light_distance, light.range);

            float angle = acos(dot(light_dir, normalize(light.direction)));
            if (angle > light.outerCutoff) {
                attenuation = 0.0;
            } else {
                float spotAtt = smoothstep(light.outerCutoff, light.innerCutoff, angle);
                attenuation *= spotAtt;
            }
        break;
    }

    //Diffuse
    float NdotL = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = light.color * u_material.baseColor * NdotL;

    //Specular
    vec3 view_dir = normalize(-position);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float NdotH = max(dot(normal, halfway_dir), 0.0);
    vec3 specular = pow(NdotH, u_material.shininess) * light.color;

    return (diffuse + specular) * light.intensity * attenuation;
}

void main()
{
    vec3 color = u_ambient_light;

    for (int i = 0; i < u_numLights; i++)
    {
        color += calculateLight(u_lights[i], fs_in.position, fs_in.normal);
    }

    vec4 texColor = texture(u_material.baseMap, fs_in.texcoord);
    f_color = texColor * vec4(color, 1.0);
}
