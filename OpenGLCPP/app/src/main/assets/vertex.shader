#version 300 es

layout(location=0) in vec3 Position;
layout(location=1) in vec3 TexCoord;

uniform mat4 gScale;

out vec4 TexCoord0;

void main()
{
    gl_Position = gScale * vec4(Position,1.0);
    TexCoord0 = vec4(TexCoord,1.0);
}