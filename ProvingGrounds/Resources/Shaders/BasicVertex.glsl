#version 330 core

layout (location = 0) in vec3 i_Pos;

void main()
{
    gl_Position = vec4(i_Pos, 1.0f);
}
