#version 450

uniform vec4 color = vec4(1,1,1,1);
uniform vec4 light_color = vec4(0, 1, 0, 1);
uniform vec3 light_source;

out vec4 final_color;

in vec3 frag_pos;
in vec3 normal;

void main()
{
	float ambient_strength = 0.1;
	vec4 ambient = ambient_strength * light_color;

	vec3 light_direction = normalize(light_source - frag_pos);
	float diff = max(dot(normal, light_direction), 0.0);
    final_color = (ambient + diff) * color;
}