#type vertex
#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjMat;

out vec4 v_Color;

void main(){
    gl_Position = u_ViewProjMat * vec4(a_Pos, 1);
    v_Color = a_Color;
}

#type fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec4 v_Color;

void main(){
    color = v_Color;
}