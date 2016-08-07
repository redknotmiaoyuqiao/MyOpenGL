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

	void InitScaleTrans(Matrix4& ScaleTrans);
	void InitRotateTrans(Matrix4& RotateTrans);
	void InitTranslationTrans(Matrix4& TranslationTrans);
public:
	Pipeline();
	~Pipeline();

	void Scale(float x,float y,float z);
	void Rotate(float x, float y, float z);
	void WorldPos(float x, float y, float z);

	const Matrix4* getTrans();
};

