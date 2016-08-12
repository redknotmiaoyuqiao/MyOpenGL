//
// Created by redknot on 8/13/16.
//

#ifndef OPENGLCPP_PIPELINE_H
#define OPENGLCPP_PIPELINE_H

#include <math.h>

#include "MYGL/Vector3f.h"
#include "MYGL/Matrix4f.h"

#define M_PI 3.14159265
#define ToRadian(x) (float) (((x) * M_PI / 180.0f))

class Pipeline {
private:
    Vector3f m_scale;
    Vector3f m_rotation;
    Vector3f m_worldPos;

    Matrix4f m_transformation;

    void InitScaleTrans(Matrix4f& mat);
    void InitRotateTrans(Matrix4f& mat);
    void InitTranslationTrans(Matrix4f& mat);
    void InitPersProjTrans(Matrix4f& mat);

    struct{
        float Fov;
        float Width;
        float Height;
        float zNear;
        float zFar;
    }m_persProj;

public:
    Pipeline();
    void Scale(float _x,float _y,float _z);
    void Rotate(float _x,float _y,float _z);
    void WorldPos(float _x,float _y,float _z);
    const Matrix4f* GetTrans();

    void SetPerspectivePro(float _Fov, float _Width, float _Height, float _zNear, float _zFar);
};



#endif //OPENGLCPP_PIPELINE_H
