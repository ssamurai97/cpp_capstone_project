#shader vertex
#version 330 core

layout (location = 0 ) in vec4 inPosition;
layout (location = 1 ) in vec2 a_texCord;
out vec2 v_texCord;
uniform mat4 u_MVP;
void main(){

    gl_Position = u_MVP * pos;
    v_texCord = texCord;
}



    #shader fragment
    #version 330 core
layout(location = 0 )out vec4 color;
in vec2 v_texCord;


uniform vec4 u_color;
uniform sampler2D u_texture;

void main(){

    vec4 texColor = texture(u_texture,v_texCord);
    color = texColor;


}