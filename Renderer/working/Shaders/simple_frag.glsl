#version 450

uniform vec3 color;
uniform vec3 light_source;
uniform vec3 light_color;
uniform sampler2D normal_map;

in VertexData 
{
    vec3 frag_pos;
    vec3 normal;
	mat3 TBN;
    vec2 uv;
} i;


out vec4 out_color;

// https://community.khronos.org/t/simple-fast-prngs/70836
float noise(vec2 co)
{
  return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec2 uv = vec2(i.uv.x, 1.0 - i.uv.y);
	
	vec3 normal = texture(normal_map, uv).rgb;
	normal = i.TBN * normalize(normal * 2.0 - 1.0);

	vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
	float graininess = 0;
	float factor = 1.75;

	vec3 light_direction = normalize(light_source - i.frag_pos);
	
	float intensity = clamp(dot(normal, light_direction), 0.0, 1.0);
	
	// Hi, this is a random number. not sure what the range is, but it's a random number.
	float noise = noise(vec2(i.frag_pos));
	
	// Likelihood of this pixel being lit.
	float bias = factor * intensity;
	
	intensity = 1.0 - smoothstep(bias, bias + graininess, noise);
	
	out_color = vec4(mix(color, light_color, intensity), 1.0);
}