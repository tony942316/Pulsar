#version 450 core

in vec3 p_Color;

uniform vec4 u_Color;

out vec4 o_Color;

void main()
{
    o_Color = vec4(p_Color, 1.0f);
}
