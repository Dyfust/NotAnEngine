#version 450

uniform vec3 light_source;
uniform sampler2D u_AtlasTexture;
uniform sampler2D u_TrimTexture;

in VertexData 
{
    vec3 frag_pos;
    vec3 normal;
    vec2 uv;
} i;

out vec4 out_color;

void main()
{
    vec2 uv = vec2(i.uv.x, 1.0 - i.uv.y);

    vec3 light_direction = normalize(light_source - i.frag_pos);
    float intensity = max(0, dot(i.normal, light_direction));

    vec4 atlas_texture = texture(u_AtlasTexture, uv);
    vec4 trim_texture = texture(u_TrimTexture, uv);

    vec4 color = atlas_texture;

    if (uv.x < 0 || uv.y < 0 || uv.x > 1 || uv.y > 1)
        color = vec4(1.0, 0.0, 0.0, 1.0);

    out_color = color;
}