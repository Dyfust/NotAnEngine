#version 450

uniform vec4 color;
uniform vec3 light_source;
uniform sampler2D u_Texture;

in VertexData 
{
	vec3 frag_pos;
	vec3 normal;
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
	vec4 ambient = vec4(0.0, 0.4, 0.0, 1.0);
	float graininess = 0;
	float factor = 1.75;

	vec3 light_direction = normalize(light_source - i.frag_pos);
	
	float intensity = clamp(dot(i.normal, light_direction), 0.0, 1.0);
	
	// Hi, this is a random number. not sure what the range is, but it's a random number.
	float noise = noise(vec2(i.frag_pos));
	
	// Likelihood of this pixel being lit.
	float bias = factor * intensity;
	
	intensity = 1 - smoothstep(bias, bias + graininess, noise);
	
	out_color = mix(color, ambient, intensity);;
}