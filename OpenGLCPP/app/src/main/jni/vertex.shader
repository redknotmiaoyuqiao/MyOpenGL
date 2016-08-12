attribute vec3 Postion;

void main(){
    gl_Position = vec4(Postion.x,Postion.y,Postion.z,1.0);
}