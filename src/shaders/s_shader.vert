//#type vertex
#version 330 core

layout(location = 0 ) in vec3 a_position;
layout(location = 1 ) in vec2 a_texcord;

uniform mat4 u_world_transform;
uniform mat4 u_view;
out vec2 v_texcord;

void main() {

    vec4 pos = vec4(a_position, 1.0);

    gl_Position = pos * u_world_transform * u_view;

    v_texcord = a_texcord;
}