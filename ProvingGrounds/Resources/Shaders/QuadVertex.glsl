#version 330 core

layout (location = 0) in vec2 i_Pos;
layout (location = 1) in vec2 i_TextureCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 p_TextureCoord;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(i_Pos, 0.0f, 1.0f);
    p_TextureCoord = i_TextureCoord;
}
