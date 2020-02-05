#version 450

uniform vec4 color;
uniform vec4 light_color = vec4(0.3, 0.3, 0.3, 1);
uniform vec3 light_source;

out vec4 final_color;

in vec3 frag_pos;
in vec3 normal;

void main()
{
	vec4 ambient = light_color;

	vec3 light_direction = normalize(light_source - frag_pos);
	
	vec3 diff_color = vec3(0.3, 0.3, 0.2);
	float diff = clamp(dot(normal, light_direction), 0.0, 1.0);
	vec3 diff_final = diff_color * diff;
	
    final_color = ambient * color + vec4(diff_final, 1);
}
