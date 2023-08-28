#version 330 core

layout (location = 0) in vec2 i_Pos;

void main()
{
    gl_Position = vec4(i_Pos, 0.0f, 1.0f);
}
