#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <string.h>

#include "LOG/logger.h"
#include "com_redknot_tool_NativeMethod.h"

using namespace std;

void AddShader(GLuint ShadlerProgram, const char* shaderText,GLenum shaderType)
{
    GLuint ShaderObj = glCreateShader(shaderType);
    if(ShaderObj == 0){
        LOG_ERROR("ShaderObj Error");
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
    if(!success){
        glGetShaderInfoLog(ShaderObj,1024,NULL,infoLog);
        LOG_ERROR("Error compiling shader type %d,'%s'\n",shaderType,infoLog);
    }

    glAttachShader(ShadlerProgram,ShaderObj);
}

void CompileShaders()
{
    GLuint ShadlerProgram = glCreateProgram();
    if(ShadlerProgram == 0){
        LOG_ERROR("ShadlerProgram Error");
        return;
    }

    char * vertex_shader = "void main(){}";
    char * fragment_shader = "void main(){}";

    AddShader(ShadlerProgram,vertex_shader,GL_VERTEX_SHADER);
    AddShader(ShadlerProgram,fragment_shader,GL_FRAGMENT_SHADER);

    glLinkProgram(ShadlerProgram);
    glUseProgram(ShadlerProgram);
}

JNIEXPORT void JNICALL Java_com_redknot_tool_NativeMethod_initialize
  (JNIEnv * env, jclass thiz, jint width, jint height)
  {
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    CompileShaders();
  }

JNIEXPORT void JNICALL Java_com_redknot_tool_NativeMethod_drawFrame
  (JNIEnv * env, jclass thiz)
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }