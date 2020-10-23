
#type vertex
#version 330 core

layout(location = 0 ) in vec3 a_Position;
layout(location = 1 ) in vec2 a_TexCord;

uniform mat4 u_world_transform;
uniform mat4 u_view;
out vec2     v_texcord;

void main() {

    vec4 pos = vec4(a_Position, 1.0);

    //gl_Position = u_world_transform * u_view * pos;
    gl_Position = u_view * pos;
    v_texcord = a_TexCord;
}


#type fragment
#version 330 core


layout(location = 0 ) out vec4 color;
in vec2 v_texcord;

uniform sampler2D u_texture;

void main(){
    color = texture(u_texture, v_texcord);
}