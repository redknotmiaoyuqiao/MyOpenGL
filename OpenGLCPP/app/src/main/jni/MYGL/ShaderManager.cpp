//
// Created by redknot on 8/12/16.
//

#include "ShaderManager.h"

ShaderManager::ShaderManager(char * _vertex_shader,char * _fragment_shader)
{
    vertex_shader = _vertex_shader;
    fragment_shader = _fragment_shader;
}

void ShaderManager::AddShader(GLuint ShadlerProgram, const char* shaderText,GLenum shaderType)
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

void ShaderManager::CompileShaders()
{
    GLuint ShadlerProgram = glCreateProgram();
    if(ShadlerProgram == 0){
        LOG_ERROR("ShadlerProgram Error");
        return;
    }

    AddShader(ShadlerProgram,vertex_shader,GL_VERTEX_SHADER);
    AddShader(ShadlerProgram,fragment_shader,GL_FRAGMENT_SHADER);

    glLinkProgram(ShadlerProgram);

    *UniformLocation = glGetUniformLocation(ShadlerProgram,"gScale");
    *gSamplerLocation = glGetUniformLocation(ShadlerProgram,"gSampler");

    glUseProgram(ShadlerProgram);
}

void ShaderManager::setUniformLocation(GLuint * _UniformLocation)
{
    UniformLocation = _UniformLocation;
}

void ShaderManager::setSamplerLocation(GLuint * _gSamplerLocation)
{
    gSamplerLocation = _gSamplerLocation;
}