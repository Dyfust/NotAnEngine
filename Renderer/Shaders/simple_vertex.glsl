#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix; 

out VertexData 
{
	vec3 frag_pos;
	vec3 normal;
	vec2 uv;
} o;

void main()
{
	o.frag_pos = vec3(model_matrix * vec4(in_position, 1));
	o.normal = vec3(model_matrix * vec4(in_normal, 0));
	o.uv = in_uv;
	
	gl_Position = (projection_view_matrix * model_matrix) * vec4(in_position, 1);
}