#version 450

struct DirectionalLight 
{
	vec4 source;
	vec4 color;
};

struct PointLight
{
	vec4 color;
	vec4 position;
	float constant;
	float linear;
	float quadratic;
};

layout(std140) uniform Engine
{
    mat4 projection_view_matrix;
    vec4 camera_position;
	DirectionalLight directional_light[2];
};

uniform vec4 color;
uniform sampler2D albedo_map;
uniform sampler2D normal_map;

in VertexData 
{
    vec3 frag_pos;
    vec3 normal;
	mat3 TBN;
    vec2 uv;
} i;


out vec4 out_color;

void main()
{
	out_color = color;
}