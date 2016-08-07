#include "Pipeline.h"

Pipeline::Pipeline()
{
	m_scale = Vector3f(1.0f,1.0f,1.0f);
	m_rotation = Vector3f(0.0f, 0.0f, 0.0f);
	m_worldPos = Vector3f(0.0f, 0.0f, 0.0f);
}


Pipeline::~Pipeline()
{
}

void Pipeline::Scale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Pipeline::Rotate(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Pipeline::WorldPos(float x, float y, float z)
{
	m_worldPos.x = x;
	m_worldPos.y = y;
	m_worldPos.z = z;
}

const Matrix4* Pipeline::getTrans()
{
	Matrix4 ScaleTrans, RotateTrans, TranslationTrans;
	InitScaleTrans(ScaleTrans);
	InitRotateTrans(RotateTrans);
	InitTranslationTrans(TranslationTrans);

	m_transformation = TranslationTrans * RotateTrans * ScaleTrans;

	return &m_transformation;
}

void Pipeline::InitScaleTrans(Matrix4& mat)
{
	mat.mat[0][0] = m_scale.x; mat.mat[0][1] = 0.0f; mat.mat[0][2] = 0.0f; mat.mat[0][3] = 0.0f;
	mat.mat[1][0] = 0.0f; mat.mat[1][1] = m_scale.y; mat.mat[1][2] = 0.0f; mat.mat[1][3] = 0.0f;
	mat.mat[2][0] = 0.0f; mat.mat[2][1] = 0.0f;	mat.mat[2][2] = m_scale.z; mat.mat[2][3] = 0.0f;
	mat.mat[3][0] = 0.0f; mat.mat[3][1] = 0.0f; mat.mat[3][2] = 0.0f; mat.mat[3][3] = 1.0f;
}

void Pipeline::InitRotateTrans(Matrix4& mat)
{
	Matrix4 rx, ry, rz;

	float x = ToRadian(m_rotation.x);
	float y = ToRadian(m_rotation.y);
	float z = ToRadian(m_rotation.z);

	rx.mat[0][0] = 1.0f; rx.mat[0][1] = 0.0f; rx.mat[0][2] = 0.0f; rx.mat[0][3] = 0.0f;
	rx.mat[1][0] = 0.0f; rx.mat[1][1] = cosf(x); rx.mat[1][2] = -sinf(x); rx.mat[1][3] = 0.0f;
	rx.mat[2][0] = 0.0f; rx.mat[2][1] = sinf(x); rx.mat[2][2] = cosf(x); rx.mat[2][3] = 0.0f;
	rx.mat[3][0] = 0.0f; rx.mat[3][1] = 0.0f; rx.mat[3][2] = 0.0f; rx.mat[3][3] = 1.0f;

	ry.mat[0][0] = cosf(y); ry.mat[0][1] = 0.0f; ry.mat[0][2] = -sinf(y); ry.mat[0][3] = 0.0f;
	ry.mat[1][0] = 0.0f; ry.mat[1][1] = 1.0f; ry.mat[1][2] = 0.0f; ry.mat[1][3] = 0.0f;
	ry.mat[2][0] = sinf(y); ry.mat[2][1] = 0.0f; ry.mat[2][2] = cosf(y); ry.mat[2][3] = 0.0f;
	ry.mat[3][0] = 0.0f; ry.mat[3][1] = 0.0f; ry.mat[3][2] = 0.0f; ry.mat[3][3] = 1.0f;

	rz.mat[0][0] = cosf(z); rz.mat[0][1] = -sinf(z); rz.mat[0][2] = 0.0f; rz.mat[0][3] = 0.0f;
	rz.mat[1][0] = sinf(z); rz.mat[1][1] = cosf(z); rz.mat[1][2] = 0.0f; rz.mat[1][3] = 0.0f;
	rz.mat[2][0] = 0.0f; rz.mat[2][1] = 0.0f; rz.mat[2][2] = 1.0f; rz.mat[2][3] = 0.0f;
	rz.mat[3][0] = 0.0f; rz.mat[3][1] = 0.0f; rz.mat[3][2] = 0.0f; rz.mat[3][3] = 1.0f;

	mat = rz * ry * rx;
}

void Pipeline::InitTranslationTrans(Matrix4& mat)
{
	mat.mat[0][0] = 1.0f; mat.mat[0][1] = 0.0f; mat.mat[0][2] = 0.0f; mat.mat[0][3] = m_worldPos.x;
	mat.mat[1][0] = 0.0f; mat.mat[1][1] = 1.0f; mat.mat[1][2] = 0.0f; mat.mat[1][3] = m_worldPos.y;
	mat.mat[2][0] = 0.0f; mat.mat[2][1] = 0.0f;	mat.mat[2][2] = 1.0f; mat.mat[2][3] = m_worldPos.z;
	mat.mat[3][0] = 0.0f; mat.mat[3][1] = 0.0f; mat.mat[3][2] = 0.0f; mat.mat[3][3] = 1.0f;
}


