//
// Created by redknot on 8/17/16.
//

#ifndef OPENGLCPP_SHADLERPROGRAM_H
#define OPENGLCPP_SHADLERPROGRAM_H

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include "../FILE/ReadFile.h"

#include "../LOG/logger.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class ShaderProgram {
private:
    AAssetManager* g_pAssetManager;
    GLuint ShadlerProgram;
public:
    ShaderProgram(AAssetManager* _g_pAssetManager);
    void Init();
    void AddShadler(GLenum shaderType,char* shaderText);
    void LinkProgram();
    GLuint GetUniformLocation(char * uniformName);
    void Begin();
};



#endif //OPENGLCPP_SHADLERPROGRAM_H
