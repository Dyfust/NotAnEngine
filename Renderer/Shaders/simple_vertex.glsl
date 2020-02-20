#version 450

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix; 
uniform float time;

out vec3 frag_pos;
out vec3 normal;
out vec2 uv;

void main()
{
	frag_pos = vec3(model_matrix * vec4(local_position, 1));
	normal = vec3(model_matrix * vec4(a_normal, 0));
	uv = a_uv;
	
	gl_Position = (projection_view_matrix * model_matrix) * vec4(local_position, 1);
}