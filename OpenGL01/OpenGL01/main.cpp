#include "../../CommonLib/common.h"
#include "../../CommonLib/Utils.cpp"
#include "../../CommonLib/math3d.h"

#include "Pipeline.h"

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <assert.h>

const char * pVS = "shader.vert";
const char * pFS = "shader.frag";

GLuint VBO;
GLuint IBO;
GLuint gScaleLocation;
GLuint gWorldLocation;

static void CreateIndexBuffer() {
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);
}

static void CreateVertexBuffer() {
	Vector3f Vertices[8];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, 0.0f, 0.0f);

	Vertices[2] = Vector3f(0.0f, -1.0f, 1.0f);
	Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

	Vertices[4] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[5] = Vector3f(0.0f, 0.0f, 1.0f);

	Vertices[6] = Vector3f(0.0f, 1.0f, 0.0f);
	Vertices[7] = Vector3f(1.0f, 1.0f, 1.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static float Scale = 0.0f;

static void RenderSenceCB() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix4 World;
	World.mat[0][0] = cosf(Scale); World.mat[0][1] = 0.0f; World.mat[0][2] = -sinf(Scale); World.mat[0][3] = 0.0f;
	World.mat[1][0] = 0.0f;	World.mat[1][1] = 1.0f;	World.mat[1][2] = 0.0f; World.mat[1][3] = 0.0f;
	World.mat[2][0] = sinf(Scale);	World.mat[2][1] = 0.0f;	World.mat[2][2] = cosf(Scale); World.mat[2][3] = 0.0f;
	World.mat[3][0] = 0.0f; World.mat[3][1] = 0.0f; World.mat[3][2] = 0.0f; World.mat[3][3] = 1.0f;

	Pipeline p;
	p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
	p.Rotate(0.0f, 0.0f,0.0f);
	//p.WorldPos(sinf(Scale),0.0f,0.0f);

	Scale = Scale + 0.1f;

	glUniformMatrix4fv(gWorldLocation, 1,GL_TRUE, (const float*)p.getTrans());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * 4, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * 4, (GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

static void KeyboardFunc( unsigned char Key,int x,int y) {
	if (Key == 'a') {
		Scale += 10.0 / 360;
	}
	else if (Key == 's') {
		Scale -= 10.0 / 360;
	}
}

static void intiGlutCallBack() {
	glutDisplayFunc(RenderSenceCB);
	glutIdleFunc(RenderSenceCB);
	glutKeyboardFunc(KeyboardFunc);
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
	cout << vs << endl;
	cout << fs << endl;

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

	//gScaleLocation = glGetUniformLocation(ShadlerProgram,"gScale");
	//assert(gScaleLocation != 0xFFFFFFFF);

	gWorldLocation = glGetUniformLocation(ShadlerProgram,"gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	CompileShaders();

	CreateVertexBuffer();
	CreateIndexBuffer();

	glutMainLoop();

	return 0;
}