//
// Created by redknot on 8/13/16.
//

#ifndef OPENGLCPP_PIPELINE_H
#define OPENGLCPP_PIPELINE_H

#include <math.h>

#include "MYGL/Vector3f.h"
#include "MYGL/Matrix4f.h"

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
    void InitCameraTransfrom(Matrix4f& CameraTrans,Matrix4f& CameraRot);

    struct{
        float Fov;
        float Width;
        float Height;
        float zNear;
        float zFar;
    }m_persProj;

    struct{
        Vector3f Pos;
        Vector3f Target;
        Vector3f Up;
    }m_camera;

public:
    Pipeline();
    void Scale(float _x,float _y,float _z);
    void Rotate(float _x,float _y,float _z);
    void WorldPos(float _x,float _y,float _z);
    const Matrix4f* GetTrans();

    void SetPerspectivePro(float _Fov, float _Width, float _Height, float _zNear, float _zFar);

    void SetCamera(const Vector3f& CameraPos,const Vector3f& CameraTarget, const Vector3f& CameraUp);
};



#endif //OPENGLCPP_PIPELINE_H
