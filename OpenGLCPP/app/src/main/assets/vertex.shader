attribute vec3 Postion;

uniform float gScale;

varying vec4 vColor;


void main(){
    gl_Position = vec4(Postion.x * gScale,Postion.y * gScale,Postion.z,1.0);
    vColor = vec4(Postion.x * gScale,Postion.y * gScale,Postion.z * gScale,1.0);
}