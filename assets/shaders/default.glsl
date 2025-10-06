#type vertex
#version 330 core

layout (location = 0) in vec3 a_Pos;

void main(){
    gl_Position = vec4(a_Pos, 1);
}

#type fragment
#version 330 core

layout (location = 0) out vec4 color;

void main(){
    color = vec4(0.79f, 0.65f, 0.96f, 1.0f);
}