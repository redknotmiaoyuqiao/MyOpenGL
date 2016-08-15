//
// Created by redknot on 8/15/16.
//

#include "LightingTechnique.h"

bool LightingTechnique::Init()
{

    if(!Technique::Init())
    {
        LOG_ERROR("aaaaaaaaa");
        return false;
    }

    if(!AddShader(GL_VERTEX_SHADER,"lighting.vs"))
    {
        return false;
    }

    if(!AddShader(GL_FRAGMENT_SHADER,"lighting.fs"))
    {
        return false;
    }

    if(!Finalize()){
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_samperLocation = GetUniformLocation("gSamper");
    m_dirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
    m_dirLightAmbientintensityLocation = GetUniformLocation("gDirectionalLight.Ambientlntensity");
}

void LightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation,1,GL_TRUE,(const GLfloat*)(&WVP.mat[0][0]));
}

void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(m_dirLightColorLocation,Light.Color.x,Light.Color.y,Light.Color.z);
    glUniform1f(m_dirLightAmbientintensityLocation,Light.Ambientintensity);
}

void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_samperLocation,TextureUnit);
}