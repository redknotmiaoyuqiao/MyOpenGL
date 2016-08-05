#include "../../CommonLib/common.h"
#include "../../CommonLib/Utils.cpp"

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

const char * pVS = "shader.vert";
const char * pFS = "shader.frag";

static void RenderSenceCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

static void intiGlutCallBack() {
	glutDisplayFunc(RenderSenceCB);
	glutIdleFunc(RenderSenceCB);
}

void CompileShaders() {
	string vs, fs;

	if (!ReadShaderFile(pVS,vs)) {
		exit(1);
	}
	if (!ReadShaderFile(pFS, fs)) {
		exit(1);
	}
	cout << vs << endl;
	cout << fs << endl;
}

int main(int argc, char** argv) {
	//init
	glutInit(&argc, argv);
	//显示模式
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//初始化窗口大小
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("OPENGL");


	GLenum res = glewInit();
	if (GLEW_OK != res) {
		printf("Error%s", glewGetErrorString(res));
		return 1;
	}

	intiGlutCallBack();

	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

	CompileShaders();

	glutMainLoop();

	return 0;
}