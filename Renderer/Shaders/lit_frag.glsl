#version 450

// Phong lighting.

// Engine defined global uniforms.
uniform Engine
{
    vec3 view_point; 
    vec3 light_source;
    vec3 light_color;
    float ambient_strength = 0.5;
} e;

// Material defined uniforms.
uniform sampler2D albedo_map;
uniform sampler2D normal_map;
uniform vec3 color;
uniform float shininess = 0.6;

in VertexData 
{
    vec3 frag_pos;
    vec3 normal;
	mat3 TBN;
    vec2 uv;
} i;

out vec4 out_color;

void main()
{
    vec2 uv = vec2(i.uv.x, 1.0 - i.uv.y);
	
	vec3 normal = texture(normal_map, uv).rgb;
	normal = i.TBN * normalize(normal * 2.0 - 1.0);
	
    vec3 light_direction = normalize(e.light_source - i.frag_pos);
    vec3 view_dir = normalize(e.view_point - i.frag_pos);
    vec3 reflect_dir = reflect(-light_direction, normal);

    float intensity = max(0, dot(normal, light_direction)); // Lambertian term.
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess * 128);

    vec3 specular = spec * e.light_color;
    vec3 diffuse = e.light_color * intensity;
    vec3 ambient = e.light_color * e.ambient_strength;
	
	vec3 tex = texture(albedo_map, uv).rgb;
	
    vec3 final_color = (ambient + diffuse + specular) * tex;
    out_color = vec4(final_color, 1.0);
}