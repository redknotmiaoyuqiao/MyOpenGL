#version 300 es

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Color;

uniform mat4 gScale;

out vec4 outColor;

void main()
{
    gl_Position = gScale * vec4(Position * 0.5,1.0);
    outColor = vec4(Color,1.0);
}