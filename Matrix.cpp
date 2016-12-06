#include "pch.h"
#include "Matrix.h"

Matrix::Matrix()
{
	mat[0][0] = 1.0f; mat[0][1] = 0.0f; mat[0][2] = 0.0f; mat[0][3] = 0.0f;
	mat[1][0] = 0.0f; mat[1][1] = 1.0f; mat[1][2] = 0.0f; mat[1][3] = 0.0f;
	mat[2][0] = 0.0f; mat[2][1] = 0.0f; mat[2][2] = 1.0f; mat[2][3] = 0.0f;
	mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = 1.0f;
}

Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	mat[0][0] = m00; mat[0][1] = m01; mat[0][2] = m02; mat[0][3] = m03;
	mat[1][0] = m10; mat[1][1] = m11; mat[1][2] = m12; mat[1][3] = m13;
	mat[2][0] = m20; mat[2][1] = m21; mat[2][2] = m22; mat[2][3] = m23;
	mat[3][0] = m30; mat[3][1] = m31; mat[3][2] = m32; mat[3][3] = m33;
}

Matrix::Matrix(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d)
{
	mat[0] = a;
	mat[1] = b;
	mat[2] = c;
	mat[3] = d;
}

Matrix::Matrix(const float src[4][4])
{
	memcpy(mat, src, 4 * 4 * sizeof(float));
}

Matrix::Matrix(const Matrix& other)
{
	memcpy(mat, other.mat, 4 * 4 * sizeof(float));
}

bool Matrix::Compare(const Matrix& other) const
{

	const float *ptr1 = reinterpret_cast<const float *>(mat);
	const float *ptr2 = reinterpret_cast<const float *>(other.mat);
	for (int i = 0; i < 4 * 4; i++) {
		if (ptr1[i] != ptr2[i]) {
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

const Vector4f& Matrix::operator[](const int index) const
{
	return mat[index];
}

Vector4f& Matrix::operator[](const int index)
{
	return mat[index];
}

Matrix& Matrix::operator*=(const Matrix& a)
{
	*this = (*this) * a;

	return *this;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	memcpy(mat, other.mat, 4 * 4 * sizeof(float));

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

Matrix Matrix::operator*(const Matrix& a) const
{
	Matrix dst;
	const float *m1Ptr = reinterpret_cast<const float *>(this);
	const float *m2Ptr = reinterpret_cast<const float *>(&a);
	float * dstPtr = reinterpret_cast<float *>(&dst);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			*dstPtr = m1Ptr[0] * m2Ptr[0 * 4 + j]
				+ m1Ptr[1] * m2Ptr[1 * 4 + j]
				+ m1Ptr[2] * m2Ptr[2 * 4 + j]
				+ m1Ptr[3] * m2Ptr[3 * 4 + j];
			dstPtr++;
		}
		m1Ptr += 4;
	}

	return dst;
}

Vector4f Matrix::operator*(const Vector4f& vec) const
{
	return Vector4f(
		mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z + mat[0][3] * vec.w,
		mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z + mat[1][3] * vec.w,
		mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z + mat[2][3] * vec.w,
		mat[3][0] * vec.x + mat[3][1] * vec.y + mat[3][2] * vec.z + mat[3][3] * vec.w);
}

Vector3f Matrix::operator*(const Vector3f& vec) const
{
	float s = mat[3].x * vec.x + mat[3].y * vec.y + mat[3].z * vec.z + mat[3].w;
	if (s == 0.0f) {
		return Vector3f(0.0f, 0.0f, 0.0f);
	}
	if (s == 1.0f) {
		return Vector3f(
			mat[0].x * vec.x + mat[0].y * vec.y + mat[0].z * vec.z + mat[0].w,
			mat[1].x * vec.x + mat[1].y * vec.y + mat[1].z * vec.z + mat[1].w,
			mat[2].x * vec.x + mat[2].y * vec.y + mat[2].z * vec.z + mat[2].w);
	}
	
	float invS = 1.0f / s;

	return Vector3f(
		(mat[0].x * vec.x + mat[0].y * vec.y + mat[0].z * vec.z + mat[0].w) * invS,
		(mat[1].x * vec.x + mat[1].y * vec.y + mat[1].z * vec.z + mat[1].w) * invS,
		(mat[2].x * vec.x + mat[2].y * vec.y + mat[2].z * vec.z + mat[2].w) * invS);
}

void Matrix::Identity()
{
	mat[0][0] = 1.0f; mat[0][1] = 0.0f; mat[0][2] = 0.0f; mat[0][3] = 0.0f;
	mat[1][0] = 0.0f; mat[1][1] = 1.0f; mat[1][2] = 0.0f; mat[1][3] = 0.0f;
	mat[2][0] = 0.0f; mat[2][1] = 0.0f; mat[2][2] = 1.0f; mat[2][3] = 0.0f;
	mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = 1.0f;
}

void Matrix::Zero()
{
	mat[0][0] = 0.0f; mat[0][1] = 0.0f; mat[0][2] = 0.0f; mat[0][3] = 0.0f;
	mat[1][0] = 0.0f; mat[1][1] = 0.0f; mat[1][2] = 0.0f; mat[1][3] = 0.0f;
	mat[2][0] = 0.0f; mat[2][1] = 0.0f; mat[2][2] = 0.0f; mat[2][3] = 0.0f;
	mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = 0.0f;
}
