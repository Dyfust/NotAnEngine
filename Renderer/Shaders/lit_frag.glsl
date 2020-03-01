#version 450

// Phong lighting.

// Engine defined global uniforms.
uniform vec3 light_source;
uniform vec3 view_point;

uniform vec3 light_color;
uniform float ambient_strength = 0.5;

// Material defined uniforms.
uniform vec3 color;
uniform float shininess = 5.5;

in VertexData 
{
    vec3 frag_pos;
    vec3 normal;
    vec2 uv;
} i;

out vec4 out_color;

void main()
{
    vec2 uv = vec2(i.uv.x, 1.0 - i.uv.y);
    vec3 light_direction = normalize(light_source - i.frag_pos);
    vec3 view_dir = normalize(view_point - i.frag_pos);
    vec3 reflect_dir = reflect(-light_direction, i.normal);

    float intensity = max(0, dot(i.normal, light_direction)); // Lambertian term.
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 16);

    vec3 specular = shininess * spec * light_color;
    vec3 diffuse = light_color * intensity;
    vec3 ambient = light_color * ambient_strength;

    vec3 final_color = (ambient + diffuse + specular) * color;
    out_color = vec4(final_color, 1.0);
}