#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_tangent;
layout(location = 3) in vec2 in_uv;

struct DirectionalLight 
{
	vec4 source;
	vec4 color;
};

layout(std140) uniform Engine 
{
	mat4 projection_view_matrix;
	vec4 camera_position;
	DirectionalLight directional_light[2];
};

uniform mat4 model_matrix; 

out VertexData 
{
	vec3 frag_pos;
	vec3 normal;
	mat3 TBN;
	vec2 uv;
} o;

void main()
{
	o.frag_pos = vec3(model_matrix * vec4(in_position, 1));
	o.normal = mat3(transpose(inverse(model_matrix))) * in_normal;
	o.uv = in_uv;
	
	gl_Position = (projection_view_matrix * model_matrix) * vec4(in_position, 1);
}