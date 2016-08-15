//
// Created by redknot on 8/15/16.
//

#ifndef OPENGLCPP_LIGHTINGTECHNIQUE_H
#define OPENGLCPP_LIGHTINGTECHNIQUE_H

#include "Technique.h"
#include "Matrix4f.h"
#include "Vector3f.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

struct DirectionalLight{
    Vector3f Color;
    float Ambientintensity;
};

class LightingTechnique : public Technique{
private:
    GLuint m_WVPLocation;
    GLuint m_samperLocation;
    GLuint m_dirLightColorLocation;
    GLuint m_dirLightAmbientintensityLocation;
public:

    LightingTechnique(AAssetManager* _g_pAssetManager):Technique(_g_pAssetManager)
    {

    }

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);

    void SetTextureUnit(unsigned int TextureUnit);

    void SetDirectionalLight(const DirectionalLight& Light);
};



#endif //OPENGLCPP_LIGHTINGTECHNIQUE_H
