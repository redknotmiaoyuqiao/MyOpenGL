#version 300 es

in vec3 TexCoord0;

out vec4 FragColor;

struct DirectionalLight
{
    vec3 Color;
    float Ambientlntensity;
};

uniform DirectionalLight gDirectionalLight;

uniform sampler2D gSamper;

void main()
{
    FragColor = texture(gSamper,TexCoord0.xy) * vec4(gDirectionalLight.Color,1.0) * gDirectionalLight.Ambientlntensity;
}