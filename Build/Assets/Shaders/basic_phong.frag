#version 460 core

in vec2 v_texcoord;
in vec3 v_color;

out vec4 f_color;

uniform struct Material
{
    sampler2D baseMap;
    vec3 baseColor;

    float shininess;
    vec2 tiling;
    vec2 offset;
} u_material;

void main()
{ 
	f_color = texture(u_material.baseMap, v_texcoord) * vec4(v_color, 1);
}