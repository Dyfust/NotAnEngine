#version 450

uniform vec4 color = vec4(1,1,1,1);
uniform vec3 light_source;

out vec4 final_color;

in vec3 out_normal;

void main()
{
	float intensity = dot(light_source, out_normal);
    final_color = color;
}