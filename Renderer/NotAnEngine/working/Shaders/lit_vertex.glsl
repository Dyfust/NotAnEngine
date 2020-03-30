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
	o.uv = in_uv;
	o.frag_pos = vec3(model_matrix * vec4(in_position, 1));
	
	mat3 new_mod = mat3(transpose(inverse(model_matrix)));
	
	o.normal = new_mod * in_normal;
	vec3 tangent = new_mod * in_tangent.xyz;
	vec3 bitangent = cross(o.normal, tangent) * in_tangent.w;
	
	vec3 T = normalize(tangent);
	vec3 B = normalize(bitangent);
	vec3 N = o.normal;
	
	o.TBN = mat3(T, B, N);

	gl_Position = (projection_view_matrix * model_matrix) * vec4(in_position, 1);
}