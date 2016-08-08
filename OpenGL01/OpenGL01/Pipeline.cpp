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

void Pipeline::InitPerspectiveProj(Matrix4& mat)
{
	const float ar = m_persProj.Width / m_persProj.Height;
	const float zNear = -m_persProj.zNear;
	const float zFar = -m_persProj.zFar;
	const float zRange = zNear - zFar;

	const float tanHalfFov = tanf(ToRadian(m_persProj.Fov / 2));

	mat.mat[0][0] = 1.0f / (tanHalfFov * ar); mat.mat[0][1] = 0.0f; mat.mat[0][2] = 0.0f; mat.mat[0][3] = 0.0f;
	mat.mat[1][0] = 0.0f; mat.mat[1][1] = 1.0f / tanHalfFov; mat.mat[1][2] = 0.0f; mat.mat[1][3] = 0.0f;
	mat.mat[2][0] = 0.0f; mat.mat[2][1] = 0.0f;	mat.mat[2][2] = (-zNear - zFar)/zRange; mat.mat[2][3] = 2.0f * zFar * zNear /zRange;
	mat.mat[3][0] = 0.0f; mat.mat[3][1] = 0.0f; mat.mat[3][2] = -1.0f; mat.mat[3][3] = 1.0f;
}

void Pipeline::SetPerspectivePro(float Fov, float Width, float Height, float zNear, float zFar)
{
	m_persProj.Fov = Fov;

	m_persProj.Width = Width;
	m_persProj.Height = Height;

	m_persProj.zNear = zNear;
	m_persProj.zFar = zFar;

}

void Pipeline::InitCameraTransform(Matrix4& CameraTrans, Matrix4& CameraRot)
{
	CameraTrans.mat[0][0] = 1.0f; CameraTrans.mat[0][1] = 0.0f; CameraTrans.mat[0][2] = 0.0f; CameraTrans.mat[0][3] = -m_camera.Pos.x;
	CameraTrans.mat[1][0] = 0.0f; CameraTrans.mat[1][1] = 1.0f; CameraTrans.mat[1][2] = 0.0f; CameraTrans.mat[1][3] = -m_camera.Pos.y;
	CameraTrans.mat[2][0] = 0.0f; CameraTrans.mat[2][1] = 0.0f;	CameraTrans.mat[2][2] = 1.0f; CameraTrans.mat[2][3] = -m_camera.Pos.z;
	CameraTrans.mat[3][0] = 0.0f; CameraTrans.mat[3][1] = 0.0f; CameraTrans.mat[3][2] = 0.0f; CameraTrans.mat[3][3] = 1.0f;

	Vector3f N = m_camera.Target;
	N.Normalize();
	Vector3f U = m_camera.Up;
	U.Normalize();
	U = U.Cross(N);

	Vector3f V = N.Cross(U);
	

	CameraRot.mat[0][0] = U.x; CameraRot.mat[0][1] = U.y; CameraRot.mat[0][2] = U.z; CameraRot.mat[0][3] = 0.0f;
	CameraRot.mat[1][0] = V.x; CameraRot.mat[1][1] = V.y; CameraRot.mat[1][2] = V.z; CameraRot.mat[1][3] = 0.0f;
	CameraRot.mat[2][0] = N.x; CameraRot.mat[2][1] = N.y;	CameraRot.mat[2][2] = N.z; CameraRot.mat[2][3] = 0.0f;
	CameraRot.mat[3][0] = 0.0f; CameraRot.mat[3][1] = 0.0f; CameraRot.mat[3][2] = 0.0f; CameraRot.mat[3][3] = 1.0f;
}

void Pipeline::setCamera(Vector3f CameraPos, Vector3f CameraTarget, Vector3f CameraUp)
{
	m_camera.Pos = CameraPos;
	m_camera.Target = CameraTarget;
	m_camera.Up = CameraUp;
}

const Matrix4* Pipeline::getTrans()
{
	Matrix4 ScaleTrans, RotateTrans, TranslationTrans,PerProjTrans,CameraTrans,CameraRot;
	InitScaleTrans(ScaleTrans);
	InitRotateTrans(RotateTrans);
	InitTranslationTrans(TranslationTrans);

	InitCameraTransform(CameraTrans, CameraRot);

	InitPerspectiveProj(PerProjTrans);

	m_transformation = PerProjTrans  *CameraRot * CameraTrans * TranslationTrans * RotateTrans * ScaleTrans;

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




