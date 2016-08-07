#version 330

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Color;

//uniform float gScale;

uniform mat4 gWorld;

out vec4 OutColor;

void main(){
	gl_Position = gWorld * vec4(Position * 0.3,1.0);
	OutColor = vec4(Color,1.0);
}