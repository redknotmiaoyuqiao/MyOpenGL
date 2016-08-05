#version 330

layout(loction=0) in vec3 Position;

void main(){
	gl_Position = vec4(Position.x,Position.y,Position.z,1.0);
}