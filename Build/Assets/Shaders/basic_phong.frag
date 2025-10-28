#version 460 core

in vec2 v_texcoord;
in vec3 v_position;
in vec3 v_normal;

out vec4 f_color;

uniform vec3 u_ambient_light;

uniform struct Light {
    vec3 position;
    vec3 color;
} u_light;

uniform struct Material {
    sampler2D baseMap;
    vec3 baseColor;
    float shininess;
    vec2 tiling;
    vec2 offset;
} u_material;

vec3 calculateLight()
{
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_light.position - v_position);
    vec3 viewDir = normalize(-v_position);
    vec3 halfway = normalize(lightDir + viewDir);

    vec3 ambient = u_ambient_light * u_material.baseColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_light.color * u_material.baseColor * diff;

    float spec = pow(max(dot(norm, halfway), 0.0), u_material.shininess);
    vec3 specular = u_light.color * spec;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 lighting = calculateLight();

    vec4 texColor = texture(u_material.baseMap, v_texcoord * u_material.tiling + u_material.offset);

    f_color = texColor * vec4(lighting, 1.0);
}
