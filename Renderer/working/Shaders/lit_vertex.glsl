#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_tangent;
layout(location = 3) in vec2 in_uv;

layout(std140) uniform Engine 
{
	mat4 projection_view_matrix;
	vec3 view_point;
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
	
	vec4 bitangent = vec4(cross(o.normal, vec3(in_tangent) * in_tangent.w), 0.0);
	vec3 T = normalize(mat3(model_matrix) * vec3(in_tangent));
	vec3 B = normalize(mat3(model_matrix) * vec3(bitangent));
	vec3 N = o.normal;
	
	o.TBN = transpose(mat3(T, B, N));
	
	gl_Position = (projection_view_matrix * model_matrix) * vec4(in_position, 1);
}