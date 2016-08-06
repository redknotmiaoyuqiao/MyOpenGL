#version 330

out vec4 FragColor;

uniform float gScale;

in vec3 color;

void main(){
	FragColor = vec4(color.x,color.y,color.z,1.0);
}