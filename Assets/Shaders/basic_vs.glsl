#version 460 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texCoord;

layout(location=0) uniform mat4 u_viewProjection;
layout(location=1) uniform mat4 u_transform;

struct VertexOutput
{
    vec4 color;
    vec2 texCoord;
};

layout(location=0) out VertexOutput v_output;

void main()
{
    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);

    v_output.color    = a_color;
    v_output.texCoord = a_texCoord;
}
