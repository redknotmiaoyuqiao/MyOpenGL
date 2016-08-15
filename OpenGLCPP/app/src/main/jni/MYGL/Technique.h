//
// Created by redknot on 8/15/16.
//

#ifndef OPENGLCPP_TECHNIQUE_H
#define OPENGLCPP_TECHNIQUE_H

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include "../FILE/ReadFile.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <list>

#define GLCheckError() (glGetError() == GL_NO_ERROR)

using namespace std;

class Technique {

private:
    typedef list<GLint> ShaderObjList;
    ShaderObjList m_ShaderObjList;
    AAssetManager* g_pAssetManager;
protected:
    bool AddShader(GLenum ShaderType,char * pFileName);

    bool Finalize();

    GLint GetUniformLocation(const char * pUniformame);

    GLint GetProgramParam(GLint param);

    GLuint m_ShaderProg;

public:
    Technique(AAssetManager* _g_pAssetManager);
    virtual ~Technique();

    virtual bool Init();

    void Enable();
};



#endif //OPENGLCPP_TECHNIQUE_H
