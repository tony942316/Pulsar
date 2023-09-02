#version 330 core

out vec4 o_FragmentColor;

in vec2 p_TextureCoord;

uniform float u_Mixture;
uniform vec4 u_Color;
uniform sampler2D u_Texture0;

void main()
{
    o_FragmentColor = mix(
        texture(u_Texture0, p_TextureCoord),
        u_Color,
        u_Mixture);
}
