#version 460 core

struct VertexOutput
{
    vec4 color;
    vec2 texCoord;
    float texIndex;
    float tilingFactor;
};

layout(location=0) in VertexOutput v_output;

layout(location=1) uniform sampler2D u_textures[32];

layout(location=0) out vec4 o_color;

void main()
{
    if (v_output.color.a <= 0.0)
        discard;

    if (v_output.texIndex < 0.0 || v_output.texIndex > 31.0)
        discard;

    o_color = v_output.color * texture(u_textures[int(v_output.texIndex)], v_output.texCoord * v_output.tilingFactor);
}
