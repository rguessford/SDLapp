#version 460 core
out vec4 color;

uniform vec4 inColor;

void main()
{
    color = vec4(inColor.x, inColor.y, inColor.z, inColor.w);
} 