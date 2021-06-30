#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D inTexture;

void main()
{
    FragColor = texture(inTexture, TexCoord);
} 