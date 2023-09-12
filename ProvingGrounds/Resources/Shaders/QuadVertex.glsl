#version 450 core

layout (location = 0) in vec2 i_Pos;
layout (location = 1) in vec2 i_TexCoord;
layout (location = 2) in vec4 i_Color;
layout (location = 3) in float i_Mix;
layout (location = 4) in float i_Tex;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 p_TexCoord;
out vec4 p_Color;
out float p_Mix;
out float p_Tex;

void main()
{
    gl_Position = u_Projection * u_View * vec4(i_Pos, 0.0f, 1.0f);
    p_TexCoord = i_TexCoord;
    p_Color = i_Color;
    p_Mix = i_Mix;
    p_Tex = i_Tex;
}
