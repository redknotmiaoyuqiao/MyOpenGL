//
// Created by redknot on 8/13/16.
//

#ifndef OPENGLCPP_TEXTURE_H
#define OPENGLCPP_TEXTURE_H

#include <string>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

using namespace std;

class Texture {

private:
    string m_filename;
    GLenum m_textureTarget;
    GLuint m_textureObj;
public:
    Texture(GLenum TextureTarget, const string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);
};



#endif //OPENGLCPP_TEXTURE_H
