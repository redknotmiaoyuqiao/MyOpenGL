#pragma  once

#define M_PI 3.14159265
#define ToRadian(x)(float)(((x) * M_PI / 180.0f))

class Vector3f
{
public:
		float x, y, z;
		Vector3f(){}
		Vector3f(float _x, float _y, float _z)
		{
				x = _x;
				y = _y;
				z = _z;
		}
};

class Matrix4 
{
public:
	float mat[4][4];

	inline Matrix4 operator*(const Matrix4& Right) {
		Matrix4 Ret;

		for (int i = 0; i < 4;i++) {
			for (int j = 0; j < 4;j++) {
				Ret.mat[i][j] = mat[i][0] * Right.mat[0][j] + Right.mat[i][1] * Right.mat[1][j] +
					mat[i][2] * Right.mat[2][j] + mat[i][3] * Right.mat[3][j];
			}
		}

		return Ret;
	}
};