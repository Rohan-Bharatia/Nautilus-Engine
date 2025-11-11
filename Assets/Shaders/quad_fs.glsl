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

    vec4 color = v_output.color;

    switch (int(v_output.texIndex))
    {
        case 0:  color *= texture(u_textures[0], v_output.texCoord * v_output.tilingFactor); break;
        case 1:  color *= texture(u_textures[1], v_output.texCoord * v_output.tilingFactor); break;
        case 2:  color *= texture(u_textures[2], v_output.texCoord * v_output.tilingFactor); break;
        case 3:  color *= texture(u_textures[3], v_output.texCoord * v_output.tilingFactor); break;
        case 4:  color *= texture(u_textures[4], v_output.texCoord * v_output.tilingFactor); break;
        case 5:  color *= texture(u_textures[5], v_output.texCoord * v_output.tilingFactor); break;
        case 6:  color *= texture(u_textures[6], v_output.texCoord * v_output.tilingFactor); break;
        case 7:  color *= texture(u_textures[7], v_output.texCoord * v_output.tilingFactor); break;
        case 8:  color *= texture(u_textures[8], v_output.texCoord * v_output.tilingFactor); break;
        case 9:  color *= texture(u_textures[9], v_output.texCoord * v_output.tilingFactor); break;
        case 10: color *= texture(u_textures[10], v_output.texCoord * v_output.tilingFactor); break;
        case 11: color *= texture(u_textures[11], v_output.texCoord * v_output.tilingFactor); break;
        case 12: color *= texture(u_textures[12], v_output.texCoord * v_output.tilingFactor); break;
        case 13: color *= texture(u_textures[13], v_output.texCoord * v_output.tilingFactor); break;
        case 14: color *= texture(u_textures[14], v_output.texCoord * v_output.tilingFactor); break;
        case 15: color *= texture(u_textures[15], v_output.texCoord * v_output.tilingFactor); break;
        case 16: color *= texture(u_textures[16], v_output.texCoord * v_output.tilingFactor); break;
        case 17: color *= texture(u_textures[17], v_output.texCoord * v_output.tilingFactor); break;
        case 18: color *= texture(u_textures[18], v_output.texCoord * v_output.tilingFactor); break;
        case 19: color *= texture(u_textures[19], v_output.texCoord * v_output.tilingFactor); break;
        case 20: color *= texture(u_textures[20], v_output.texCoord * v_output.tilingFactor); break;
        case 21: color *= texture(u_textures[21], v_output.texCoord * v_output.tilingFactor); break;
        case 22: color *= texture(u_textures[22], v_output.texCoord * v_output.tilingFactor); break;
        case 23: color *= texture(u_textures[23], v_output.texCoord * v_output.tilingFactor); break;
        case 24: color *= texture(u_textures[24], v_output.texCoord * v_output.tilingFactor); break;
        case 25: color *= texture(u_textures[25], v_output.texCoord * v_output.tilingFactor); break;
        case 26: color *= texture(u_textures[26], v_output.texCoord * v_output.tilingFactor); break;
        case 27: color *= texture(u_textures[27], v_output.texCoord * v_output.tilingFactor); break;
        case 28: color *= texture(u_textures[28], v_output.texCoord * v_output.tilingFactor); break;
        case 29: color *= texture(u_textures[29], v_output.texCoord * v_output.tilingFactor); break;
        case 30: color *= texture(u_textures[30], v_output.texCoord * v_output.tilingFactor); break;
        case 31: color *= texture(u_textures[31], v_output.texCoord * v_output.tilingFactor); break;
        default: discard;
    }

    o_color = color;
}
