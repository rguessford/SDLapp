// vs.glsl
#version 460 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 color;


out vec2 TexCoord;
out vec4 vColor;

void main()
{
    gl_Position = vec4(position.x,position.y,0.0,1.0);
    TexCoord = aTexCoord;
}