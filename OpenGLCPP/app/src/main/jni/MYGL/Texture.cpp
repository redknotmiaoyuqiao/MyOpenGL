//
// Created by redknot on 8/13/16.
//

#include "Texture.h"


Texture::Texture(AAssetManager* _g_pAssetManager,GLenum TextureTarget, const string& FileName)
{
    m_textureTarget = TextureTarget;
    m_filename = FileName;
    g_pAssetManager = _g_pAssetManager;
}

bool Texture::Load()
{
    ReadPNG r;
    string png_src = m_filename;
    ImageData* img_res = r.FromAssetPNGFile(g_pAssetManager,png_src);

    LOG_ERROR("width: %d",img_res->img_width);
    LOG_ERROR("height: %d",img_res->img_height);

    glGenTextures(1,&m_textureObj);
    glBindTexture(m_textureTarget,m_textureObj);
    glTexImage2D(m_textureTarget,0,GL_RGBA,img_res->img_width,img_res->img_height,0,GL_RGBA,GL_UNSIGNED_BYTE,img_res->pixels);

    glTexParameterf(m_textureTarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(m_textureTarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    delete img_res;

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget,m_textureObj);
}