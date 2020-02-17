#version 450

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix; 
uniform float time;

out vec3 frag_pos;
out vec3 normal;

void main()
{
	frag_pos = vec3(model_matrix * vec4(local_position, 1));
	normal = vec3(model_matrix * vec4(a_normal, 0));
	
	vec3 pos = vec3(local_position);
	float max = 0.25;
	float mul = max / 2.0;
	//pos += normal * clamp((sin(time) + 1.0) * mul, 0.0, max);
	
	gl_Position = (projection_view_matrix * model_matrix) * vec4(pos, 1);
}