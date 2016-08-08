#pragma once

#include "../../CommonLib/math3d.h"
#include <math.h>

class Pipeline
{
private:
	Matrix4 m_transformation;

	Vector3f m_scale;
	Vector3f m_rotation;
	Vector3f m_worldPos;

	struct {
		float Fov;
		float Width;
		float Height;
		float zNear;
		float zFar;
	} m_persProj;

	struct 
	{
		Vector3f Pos;
		Vector3f Target;
		Vector3f Up;
	}m_camera;


	void InitScaleTrans(Matrix4& ScaleTrans);
	void InitRotateTrans(Matrix4& RotateTrans);
	void InitTranslationTrans(Matrix4& TranslationTrans);
	void InitPerspectiveProj(Matrix4& TranslationTrans);
	void InitCameraTransform(Matrix4& CameraTrans, Matrix4& CameraRot);
public:
	Pipeline();
	~Pipeline();

	void Scale(float x,float y,float z);
	void Rotate(float x, float y, float z);
	void WorldPos(float x, float y, float z);

	const Matrix4* getTrans();

	void SetPerspectivePro(float Fov, float Width, float Height, float zNear, float zFar);

	void setCamera(Vector3f CameraPos, Vector3f CameraTarget, Vector3f CameraUp);
};

