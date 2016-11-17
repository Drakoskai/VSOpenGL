#include "Matrix.h"

Matrix::Matrix()
{
	mat[0] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	mat[1] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	mat[2] = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	mat[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	mat[0] = Vector4(m00, m01, m02, m03);
	mat[1] = Vector4(m10, m11, m12, m13);
	mat[2] = Vector4(m20, m21, m22, m23);
	mat[3] = Vector4(m30, m31, m32, m33);
}

Matrix::Matrix(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
{
	mat[0] = row0;
	mat[1] = row1;
	mat[2] = row2;
	mat[3] = row3;
}

Matrix::Matrix(const Matrix& other)
{
	mat[0] = other.mat[0];
	mat[1] = other.mat[0];
	mat[2] = other.mat[0];
	mat[3] = other.mat[0];
}

bool Matrix::Compare(const Matrix& other) const
{
	for (int i = 0; i < 4; i++) {
		if (mat[i] != other.mat[i]) {
			return false;
		}
	}

	return true;
}

bool Matrix::operator==(const Matrix& other) const
{
	return Compare(other);
}

bool Matrix::operator!=(const Matrix& other) const
{
	return !Compare(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	mat[0] = other.mat[0];
	mat[1] = other.mat[0];
	mat[2] = other.mat[0];
	mat[3] = other.mat[0];

	return *this;
}

Matrix Matrix::operator*(const float s) const
{
	return Matrix(
		mat[0].x * s, mat[0].y * s, mat[0].z * s, mat[0].w * s,
		mat[1].x * s, mat[1].y * s, mat[1].z * s, mat[1].w * s,
		mat[2].x * s, mat[2].y * s, mat[2].z * s, mat[2].w * s,
		mat[3].x * s, mat[3].y * s, mat[3].z * s, mat[3].w * s);
}

void Matrix::Identity()
{
	mat[0] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	mat[1] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	mat[2] = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	mat[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}
