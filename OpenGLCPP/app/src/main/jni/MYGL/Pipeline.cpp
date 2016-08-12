//
// Created by redknot on 8/13/16.
//

#include "Pipeline.h"


Pipeline::Pipeline()
{
    m_scale = Vector3f(1.0f,1.0f,1.0f);
    m_rotation = Vector3f(0.0f,0.0f,0.0f);
    m_worldPos = Vector3f(0.0f,0.0f,0.0f);
}

void Pipeline::Scale(float _x,float _y,float _z)
{
    m_scale.x = _x;
    m_scale.y = _y;
    m_scale.z = _z;
}

void Pipeline::Rotate(float _x,float _y,float _z)
{
    m_rotation.x = _x;
    m_rotation.y = _y;
    m_rotation.z = _z;
}

void Pipeline::WorldPos(float _x,float _y,float _z)
{
    m_worldPos.x = _x;
    m_worldPos.y = _y;
    m_worldPos.z = _z;
}

void Pipeline::InitScaleTrans(Matrix4f& mat)
{
    mat.mat[0][0] = m_scale.x;mat.mat[0][1] = 0.0f;mat.mat[0][2] = 0.0f;mat.mat[0][3] = 0.0f;
    mat.mat[1][0] = 0.0f;mat.mat[1][1] = m_scale.y;mat.mat[1][2] = 0.0f;mat.mat[1][3] = 0.0f;
    mat.mat[2][0] = 0.0f;mat.mat[2][1] = 0.0f;mat.mat[2][2] = m_scale.z;mat.mat[2][3] = 0.0f;
    mat.mat[3][0] = 0.0f;mat.mat[3][1] = 0.0f;mat.mat[3][2] = 0.0f;mat.mat[3][3] = 1.0f;
}

void Pipeline::InitRotateTrans(Matrix4f& mat)
{
    Matrix4f rx,ry,rz;

    const float x = ToRadian(m_rotation.x);
    const float y = ToRadian(m_rotation.y);
    const float z = ToRadian(m_rotation.z);

    rx.mat[0][0] = 1.0f;rx.mat[0][1] = 0.0f;rx.mat[0][2] = 0.0f;rx.mat[0][3] = 0.0f;
    rx.mat[1][0] = 0.0f;rx.mat[1][1] = cosf(x);rx.mat[1][2] = -sinf(x);rx.mat[1][3] = 0.0f;
    rx.mat[2][0] = 0.0f;rx.mat[2][1] = sinf(x);rx.mat[2][2] = cosf(x);rx.mat[2][3] = 0.0f;
    rx.mat[3][0] = 0.0f;rx.mat[3][1] = 0.0f;rx.mat[3][2] = 0.0f;rx.mat[3][3] = 1.0f;

    ry.mat[0][0] = cosf(y);ry.mat[0][1] = 0.0f;ry.mat[0][2] = -sinf(y);ry.mat[0][3] = 0.0f;
    ry.mat[1][0] = 0.0f;ry.mat[1][1] = 1.0f;ry.mat[1][2] = 0.0f;ry.mat[1][3] = 0.0f;
    ry.mat[2][0] = sinf(y);ry.mat[2][1] = 0.0f;ry.mat[2][2] = cosf(y);ry.mat[2][3] = 0.0f;
    ry.mat[3][0] = 0.0f;ry.mat[3][1] = 0.0f;ry.mat[3][2] = 0.0f;ry.mat[3][3] = 1.0f;

    rz.mat[0][0] = cosf(z);rz.mat[0][1] = -sinf(z);rz.mat[0][2] = 0.0f;rz.mat[0][3] = 0.0f;
    rz.mat[1][0] = sinf(z);rz.mat[1][1] = cos(z);rz.mat[1][2] = 0.0f;rz.mat[1][3] = 0.0f;
    rz.mat[2][0] = 0.0f;rz.mat[2][1] = 0.0f;rz.mat[2][2] = 1.0f;rz.mat[2][3] = 0.0f;
    rz.mat[3][0] = 0.0f;rz.mat[3][1] = 0.0f;rz.mat[3][2] = 0.0f;rz.mat[3][3] = 1.0f;

    mat = rz * ry * rx;
}

void Pipeline::InitTranslationTrans(Matrix4f& mat)
{
    mat.mat[0][0] = 1.0f;mat.mat[0][1] = 0.0f;mat.mat[0][2] = 0.0f;mat.mat[0][3] = m_worldPos.x;
    mat.mat[1][0] = 0.0f;mat.mat[1][1] = 1.0f;mat.mat[1][2] = 0.0f;mat.mat[1][3] = m_worldPos.y;
    mat.mat[2][0] = 0.0f;mat.mat[2][1] = 0.0f;mat.mat[2][2] = 1.0f;mat.mat[2][3] = m_worldPos.z;
    mat.mat[3][0] = 0.0f;mat.mat[3][1] = 0.0f;mat.mat[3][2] = 0.0f;mat.mat[3][3] = 1.0f;
}

void Pipeline::InitPersProjTrans(Matrix4f& mat)
{
    const float ar = m_persProj.Width / m_persProj.Height;
    const float zNear = -m_persProj.zNear;
    const float zFar = -m_persProj.zFar;
    const float zRange = zNear - zFar;
    const float tanHalfFov = tanf(ToRadian(m_persProj.Fov / 2));

    mat.mat[0][0] = 1.0f / (ar * tanHalfFov);mat.mat[0][1] = 0.0f;mat.mat[0][2] = 0.0f;mat.mat[0][3] = 0.0f;
    mat.mat[1][0] = 0.0f;mat.mat[1][1] = 1.0f / (tanHalfFov);mat.mat[1][2] = 0.0f;mat.mat[1][3] = 0.0f;
    mat.mat[2][0] = 0.0f;mat.mat[2][1] = 0.0f;mat.mat[2][2] = (-zNear-zFar)/zRange;mat.mat[2][3] = (2.0f * zNear * zFar)/zRange;
    mat.mat[3][0] = 0.0f;mat.mat[3][1] = 0.0f;mat.mat[3][2] = -1.0f;mat.mat[3][3] = 0.0f;
}

void Pipeline::SetPerspectivePro(float _Fov, float _Width, float _Height, float _zNear, float _zFar)
{
    m_persProj.Fov = _Fov;
    m_persProj.Width = _Width;
    m_persProj.Height = _Height;
    m_persProj.zNear = _zNear;
    m_persProj.zFar = _zFar;
}

const Matrix4f* Pipeline::GetTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans, PersProjTrans;

    InitScaleTrans(ScaleTrans);
    InitRotateTrans(RotateTrans);
    InitTranslationTrans(TranslationTrans);
    InitPersProjTrans(PersProjTrans);

    m_transformation = PersProjTrans * TranslationTrans * RotateTrans * ScaleTrans;

    return &(m_transformation);
}