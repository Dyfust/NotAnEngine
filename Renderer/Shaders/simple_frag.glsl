#version 450

uniform vec4 color;
uniform vec4 ambient = vec4(196.0 / 255.0, 176.0 / 255.0, 228.0 / 255.0, 1.0);
uniform vec3 light_source;
uniform float time;
uniform sampler2D u_Texture;

out vec4 final_color;

in vec3 frag_pos;
in vec3 normal;
in vec2 uv;

float noised(vec2 co)
{
  return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec3 light_direction = normalize(light_source - frag_pos);
	
	float intensity = clamp(dot(normal, light_direction), 0.0, 1.0);
	
	float noise = noised(vec2(frag_pos));
	
	float bias = 1.75 * intensity;//2.25 * intensity;
	
	float new_intensity = 0;
	
	if (noise < bias)
	new_intensity = 1;
	else
	new_intensity = 0;
	
	if (intensity > 0.6)
	new_intensity = 1;
	
	float toon_intensity = smoothstep(0.4, 0.4, intensity);
	
	vec4 new_color = mix(color, ambient, toon_intensity * new_intensity);
	
	final_color = new_color;
}
