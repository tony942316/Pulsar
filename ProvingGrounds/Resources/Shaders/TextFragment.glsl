#version 450 core

out vec4 o_FragmentColor;

in vec2 p_TexCoord;
in vec4 p_Color;
in float p_Tex;

uniform sampler2D u_Textures[32];

void main()
{
    o_FragmentColor =
        vec4(1.0, 1.0, 1.0, texture(u_Textures[int(p_Tex)], p_TexCoord).r) *
        p_Color;
}
