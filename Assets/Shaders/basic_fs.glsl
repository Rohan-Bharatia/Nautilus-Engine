#version 460 core

struct VertexOutput
{
    vec4 color;
    vec2 texCoord;
};

layout(location=0) in VertexOutput v_output;

layout(binding=2) uniform sampler2D u_texture;

layout(location=0) out vec4 o_color;

void main()
{
    o_color = v_output.color * texture(u_texture, v_output.texCoord);
}
