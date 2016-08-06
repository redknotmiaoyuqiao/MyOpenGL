#version 330

layout(location=0) in vec3 Position;

uniform float gScale;

out vec3 color;

void main(){
	gl_Position = vec4(Position.x * gScale ,Position.y * gScale,Position.z,1.0);
	color = vec3(Position.x,Position.y,Position.z);
}