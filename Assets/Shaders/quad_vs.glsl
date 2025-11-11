#version 460 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texCoord;
layout(location=3) in float a_texIndex;
layout(location=4) in float a_tilingFactor;

layout(location=0) uniform mat4 u_viewProjection;

struct VertexOutput
{
    vec4 color;
    vec2 texCoord;
    float texIndex;
    float tilingFactor;
};

layout(location=0) out VertexOutput v_output;

void main()
{
    gl_Position = u_viewProjection * vec4(a_position, 1.0);

    v_output.color        = a_color;
    v_output.texCoord     = a_texCoord;
    v_output.texIndex     = a_texIndex;
    v_output.tilingFactor = a_tilingFactor;
}
