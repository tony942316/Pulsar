#version 450 core

layout (location = 0) in vec3 i_Pos;
layout (location = 1) in vec3 i_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 p_Color;

void main()
{
    p_Color = i_Color;
    gl_Position = u_Projection * u_View * u_Model * vec4(i_Pos, 1.0f);
}
