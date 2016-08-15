#version 300 es

out vec4 FragColor;

in vec4 TexCoord0;

uniform sampler2D gSampler;

void main()
{
    FragColor = texture(gSampler,TexCoord0.xy) * vec4(1.0,1.0,1.0,1.0) * 1.0;
}