#version 450

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix; 

out vec3 frag_pos;
out vec3 normal;

void main()
{
	gl_Position = (projection_view_matrix * model_matrix) * vec4(local_position, 1);
	frag_pos = vec3(model_matrix * vec4(local_position, 1));
	normal = normalize(a_normal);
}