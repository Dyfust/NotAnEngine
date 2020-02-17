#version 450

uniform vec4 color;
uniform vec4 light_color = vec4(0.25, 0.25, 0.25, 1);
uniform vec3 light_source;
uniform float time;

out vec4 final_color;

in vec3 frag_pos;
in vec3 normal;

void main()
{
	vec4 ambient = light_color;

	vec3 light_direction = normalize(light_source - frag_pos);
	
	vec4 diff_color;
	float intensity = clamp(dot(normal, light_direction), 0.0, 1.0);
	
	if (intensity > 0.95)  
		diff_color = vec4(0.9, 0.9, 0.9, 1.0);
    //else if 
		//(intensity > 0.75) diff_color = vec4(0.8, 0.8, 0.8, 1.0);
    else if 
		(intensity > 0.50) diff_color = vec4(0.6, 0.6, 0.6, 1.0);
    //else if 
		//(intensity > 0.25) diff_color = vec4(0.4, 0.4, 0.4, 1.0);
    else                       
		diff_color = vec4(0.2, 0.2, 0.2, 1.0);
	
	vec4 diff_final = diff_color;
	
	
    final_color = ambient * color + diff_color;
	//final_color = vec4(normal, 1.0) * color;
}
