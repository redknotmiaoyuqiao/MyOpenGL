//
// Created by redknot on 8/15/16.
//

#include "Technique.h"


Technique::Technique(AAssetManager* _g_pAssetManager)
{
    g_pAssetManager = _g_pAssetManager;
    m_ShaderProg = 0;
}

Technique::~Technique()
{
    for(ShaderObjList::iterator it = m_ShaderObjList.begin();it != m_ShaderObjList.end();it++){
        glDeleteShader(*it);
    }

    if(m_ShaderProg != 0){
        glDeleteProgram(m_ShaderProg);
        m_ShaderProg = 0;
    }
}

bool Technique::Init()
{
    m_ShaderProg = glCreateProgram();

    if(m_ShaderProg == 0){
        LOG_ERROR("Create Shader Program Fail!");
        return false;
    }

    return true;
}

bool Technique::AddShader(GLenum ShaderType,char * pFileName)
{

    ReadFile read = ReadFile(g_pAssetManager);
    char * shaderText = read.readShaderSrcFile(pFileName);

    GLuint ShaderObj = glCreateShader(ShaderType);
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
        LOG_ERROR("Error compiling shader type %d,'%s'\n",ShaderType,infoLog);
    }

    glAttachShader(m_ShaderProg,ShaderObj);

    return true;
}

bool Technique::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024];

    glLinkProgram(m_ShaderProg);

    glGetProgramiv(m_ShaderProg,GL_LINK_STATUS,&Success);
    if(Success == 0){
        glGetProgramInfoLog(m_ShaderProg,sizeof(ErrorLog),NULL,ErrorLog);
        LOG_ERROR("Error Linking shader program '%s'\n",ErrorLog);
        return false;
    }

    glValidateProgram(m_ShaderProg);
    glGetProgramiv(m_ShaderProg,GL_LINK_STATUS,&Success);
    if(!Success){
        glGetProgramInfoLog(m_ShaderProg,sizeof(ErrorLog),NULL,ErrorLog);
        LOG_ERROR("Invalid shader program:'%s'\n",ErrorLog);
        return false;
    }

    for(ShaderObjList::iterator it = m_ShaderObjList.begin();it != m_ShaderObjList.end();it++){
        glDeleteShader(*it);
    }

    m_ShaderObjList.clear();

    return GLCheckError();
}

void Technique::Enable()
{
    glUseProgram(m_ShaderProg);
}


GLint Technique::GetUniformLocation(const char * pUniformame)
{
    GLuint Location = glGetUniformLocation(m_ShaderProg,pUniformame);

    if(Location == 0xFFFFFFFFFFFFF)
    {
        LOG_ERROR("Unable to get the location of uniform :'%s'\n",pUniformame);
    }

    return Location;
}


GLint Technique::GetProgramParam(GLint param)
{
    GLint ret;

    glGetProgramiv(m_ShaderProg,param,&ret);

    return ret;
}