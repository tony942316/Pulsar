#version 330 core

layout (location = 0) in vec3 i_Pos;
layout (location = 1) in vec3 i_Trans;
layout (location = 2) in vec3 i_Scale;

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    mat4 trans;
    trans[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
    trans[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
    trans[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
    trans[3] = vec4(i_Trans.x, i_Trans.y, i_Trans.z, 1.0f);
    mat4 scale;
    scale[0] = vec4(i_Scale.x, 0.0f, 0.0f, 0.0f);
    scale[1] = vec4(0.0f, i_Scale.y, 0.0f, 0.0f);
    scale[2] = vec4(0.0f, 0.0f, i_Scale.z, 0.0f);
    scale[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    mat4 model = trans * scale;
    gl_Position = u_Projection * u_View * model * vec4(i_Pos, 1.0f);
}
