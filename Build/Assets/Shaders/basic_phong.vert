#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;
layout(location = 2) in vec3 a_normal;



out VS_OUT
{
    vec2 texcoord;
    vec3 position;
    vec3 normal;
} vs_out;

struct Material {
    vec3 baseColor;
    vec3 emissiveColor;
    float shininess;
    vec2 tiling;
    vec2 offset;
    uint parameters;
};

uniform Material u_material;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    vs_out.texcoord = (a_texcoord * u_material.tiling) + u_material.offset;
    mat4 model_view = u_view * u_model;
    vec4 view_pos = model_view * vec4(a_position, 1.0);
    vs_out.position = view_pos.xyz;
    vs_out.normal = normalize(mat3(model_view) * a_normal);
    gl_Position = u_projection * view_pos;
}
