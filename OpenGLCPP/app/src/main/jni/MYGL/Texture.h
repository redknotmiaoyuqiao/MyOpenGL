//
// Created by redknot on 8/13/16.
//

#ifndef OPENGLCPP_TEXTURE_H
#define OPENGLCPP_TEXTURE_H

#include <string>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "FILE/ReadPNG.h"
#include "FILE/ImageData.h"

using namespace std;

class Texture {

private:
    AAssetManager* g_pAssetManager;
    string m_filename;
    GLenum m_textureTarget;
    GLuint m_textureObj;
public:
    Texture(AAssetManager* _g_pAssetManager,GLenum TextureTarget, const string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);
};



#endif //OPENGLCPP_TEXTURE_H
