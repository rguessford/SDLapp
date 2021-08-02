#version 460 core
out vec4 FragColor;

in vec4 vColor;

void main()
{
    FragColor = vec4(vColor.x, vColor.y, vColor.z, vColor.w);
} 