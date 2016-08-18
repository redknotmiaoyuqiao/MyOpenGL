//
// Created by redknot on 8/17/16.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(AAssetManager* _g_pAssetManager)
{
    g_pAssetManager = _g_pAssetManager;
}

void ShaderProgram::Init()
{
    ShadlerProgram = glCreateProgram();
    if(ShadlerProgram == 0){
        LOG_ERROR("ShadlerProgram Error");
        return;
    }
}

void ShaderProgram::AddShadler(GLenum shaderType,char* shaderFile)
{
    ReadFile read = ReadFile(g_pAssetManager);

    char * shaderText = read.readShaderSrcFile(shaderFile);

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

void ShaderProgram::LinkProgram()
{
    glLinkProgram(ShadlerProgram);
}

GLuint ShaderProgram::GetUniformLocation(char * uniformName)
{
    GLuint UniformLocation = glGetUniformLocation(ShadlerProgram,uniformName);
    return UniformLocation;
}

void ShaderProgram::Begin()
{
    glUseProgram(ShadlerProgram);
}