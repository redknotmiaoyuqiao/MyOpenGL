#include "../../CommonLib/common.h"
#include "../../CommonLib/Utils.cpp"
#include "../../CommonLib/math3d.h"

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <assert.h>

const char * pVS = "shader.vert";
const char * pFS = "shader.frag";

GLuint VBO;
GLuint gScaleLocation;

static void CreateVertexBuffer() {
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void RenderSenceCB() {
	glClear(GL_COLOR_BUFFER_BIT);

	static float Scale = 0.0f;
	Scale = Scale + 0.01f;
	glUniform1f(gScaleLocation, sinf(Scale));

	glEnableVertexAttribArray(0);

	CreateVertexBuffer();

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*4,0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void intiGlutCallBack() {
	glutDisplayFunc(RenderSenceCB);
	glutIdleFunc(RenderSenceCB);
}

static void AddShader(GLuint ShadlerProgram,const char* shaderText,GLenum shaderType) {
	GLuint ShaderObj = glCreateShader(shaderType);
	if (ShaderObj == 0) {
		ErrorOut();
		exit(1);
	}

	const GLchar* p[1];
	p[0] = shaderText;
	GLint L[1];
	L[0] = strlen(shaderText);

	glShaderSource(ShaderObj,1,p,L);

	glCompileShader(ShaderObj);

	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(ShaderObj,GL_COMPILE_STATUS,&success);
	if (!success) {
		glGetShaderInfoLog(ShaderObj,1024,NULL,infoLog);
		fprintf(stderr,"Error compiling shader type %d,'%s'\n",shaderType,infoLog);
		exit(1);
	}

	glAttachShader(ShadlerProgram, ShaderObj);
}

void CompileShaders() {
	string vs, fs;

	if (!ReadShaderFile(pVS,vs)) {
		exit(1);
	}
	if (!ReadShaderFile(pFS, fs)) {
		exit(1);
	}
	//cout << vs << endl;
	//cout << fs << endl;

	GLuint ShadlerProgram = glCreateProgram();
	if (ShadlerProgram == 0) {
		ErrorOut();
		exit(1);
	}

	AddShader(ShadlerProgram,vs.c_str(),GL_VERTEX_SHADER);
	AddShader(ShadlerProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	glLinkProgram(ShadlerProgram);

	GLint success;
	GLchar ErrorLog[1024];
	glGetShaderiv(ShadlerProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ShadlerProgram, 1024, NULL, ErrorLog);
		fprintf(stderr, "Error linking shader type,'%s'\n", ErrorLog);
		exit(1);
	}

	gScaleLocation = glGetUniformLocation(ShadlerProgram,"gScale");
	assert(gScaleLocation != 0xFFFFFFFF);

	glValidateProgram(ShadlerProgram);
	glGetShaderiv(ShadlerProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ShadlerProgram, 1024, NULL, ErrorLog);
		fprintf(stderr, "Error linking shader type,'%s'\n", ErrorLog);
		exit(1);
	}

	glUseProgram(ShadlerProgram);
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