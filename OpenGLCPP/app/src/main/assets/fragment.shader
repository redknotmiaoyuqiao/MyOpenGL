#version 300 es

out vec4 FragColor;

in vec4 outColor;

void main()
{
    FragColor = outColor;
}