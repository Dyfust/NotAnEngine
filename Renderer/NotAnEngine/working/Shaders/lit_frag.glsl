#version 450

// Phong lighting.
// Struct definitions.
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

// Engine defined global uniforms.
//uniform DirectionalLight directional_light;
uniform float ambient_strength = 0.5;

// Material defined uniforms.
uniform sampler2D albedo_map;
uniform sampler2D normal_map;
uniform vec4 object_color;
uniform float shininess;
uniform float specular_reflectance;

in VertexData 
{
    vec3 frag_pos;
    vec3 normal;
	mat3 TBN;
    vec2 uv;
} i;

out vec4 out_color;

vec3 DoPhong(vec3 light_direction, vec3 light_color, vec3 normal, vec3 view_direction)
{
	vec3 reflect_direction = reflect(-light_direction, normal);

	float lambertian = max(dot(normal, light_direction), 0.0);
	float spec = pow(max(dot(reflect_direction, view_direction), 0.0), shininess * 128);
	vec3 specular = specular_reflectance * spec * light_color;
    vec3 diffuse = light_color * lambertian;
    vec3 ambient = light_color * ambient_strength;
	
	return ambient + diffuse + specular;
}

vec3 CalculateDirectionalLight(DirectionalLight directional_light, vec3 frag_position, vec3 normal, vec3 view_direction)
{
	vec3 light_direction = normalize(directional_light.source.xyz - frag_position);
	return DoPhong(light_direction, directional_light.color.xyz, normal, view_direction);
}

vec3 CalculatePointLight(PointLight point_light, vec3 frag_position, vec3 normal, vec3 view_direction)
{
	vec3 light_direction = normalize(point_light.position.xyz - frag_position);
	vec3 col = DoPhong(light_direction, point_light.color.xyz, normal, view_direction);
	float distance = length(point_light.position.xyz - frag_position);
	float attenuation = 1.0 / (point_light.constant + point_light.linear * distance + point_light.quadratic * (distance * distance));
	
	return col * attenuation;
}

void main()
{
    vec2 uv = vec2(i.uv.x, 1.0 - i.uv.y);
	vec3 normal = texture(normal_map, uv).xyz * 2.0 - 1.0;
	normal = i.TBN * normal;
	
	vec3 view_point = vec3(camera_position); 
    vec3 view_dir = normalize(view_point - i.frag_pos);
	
	vec3 lighting_color = vec3(0.0, 0.0, 0.0);
	for (int light = 0; light < 1; ++light)
	{
		lighting_color += CalculateDirectionalLight(directional_light[light], i.frag_pos, normal, view_dir);
	}
	
	vec3 texture_color = texture(albedo_map, uv).rgb;
    out_color = vec4(lighting_color * texture_color * object_color.rgb, 1.0);
}
