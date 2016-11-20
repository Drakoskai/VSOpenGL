#include "Matrix.h"

Matrix::Matrix()
{
	mat[0] = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
	mat[1] = Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
	mat[2] = Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
	mat[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	mat[0] = Vector4f(m00, m01, m02, m03);
	mat[1] = Vector4f(m10, m11, m12, m13);
	mat[2] = Vector4f(m20, m21, m22, m23);
	mat[3] = Vector4f(m30, m31, m32, m33);
}

Matrix::Matrix(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3)
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

Matrix& Matrix::operator*=(const Matrix& other) 
{
	// Row 1
	mat[0].x = (mat[0].x * other.mat[0].x) + (mat[0].y * other.mat[1].x) + (mat[0].z * other.mat[2].x) + (mat[0].w * other.mat[3].x);
	mat[0].y = (mat[0].x * other.mat[0].y) + (mat[0].y * other.mat[1].y) + (mat[0].z * other.mat[2].y) + (mat[0].w * other.mat[3].y);
	mat[0].z = (mat[0].x * other.mat[0].z) + (mat[0].y * other.mat[1].z) + (mat[0].z * other.mat[2].z) + (mat[0].w * other.mat[3].z);
	mat[0].w = (mat[0].x * other.mat[0].w) + (mat[0].y * other.mat[1].w) + (mat[0].z * other.mat[2].w) + (mat[0].w * other.mat[3].w);
	
	// Row 2
	mat[1].x = (mat[1].x * other.mat[0].x) + (mat[1].y * other.mat[1].x) + (mat[1].z * other.mat[2].x) + (mat[1].w * other.mat[3].x);
	mat[1].y = (mat[1].x * other.mat[0].y) + (mat[1].y * other.mat[1].y) + (mat[1].z * other.mat[2].y) + (mat[1].w * other.mat[3].y);
	mat[1].z = (mat[1].x * other.mat[0].z) + (mat[1].y * other.mat[1].z) + (mat[1].z * other.mat[2].z) + (mat[1].w * other.mat[3].z);
	mat[1].w = (mat[1].x * other.mat[0].w) + (mat[1].y * other.mat[1].w) + (mat[1].z * other.mat[2].w) + (mat[1].w * other.mat[3].w);
	
	// Row 3
	mat[2].x = (mat[2].x * other.mat[0].x) + (mat[2].y * other.mat[1].x) + (mat[2].z * other.mat[2].x) + (mat[2].w * other.mat[3].x);
	mat[2].y = (mat[2].x * other.mat[0].y) + (mat[2].y * other.mat[1].y) + (mat[2].z * other.mat[2].y) + (mat[2].w * other.mat[3].y);
	mat[2].z = (mat[2].x * other.mat[0].z) + (mat[2].y * other.mat[1].z) + (mat[2].z * other.mat[2].z) + (mat[2].w * other.mat[3].z);
	mat[2].w = (mat[2].x * other.mat[0].w) + (mat[2].y * other.mat[1].w) + (mat[2].z * other.mat[2].w) + (mat[2].w * other.mat[3].w);
	
	// Row 4
	mat[3].x = (mat[3].x * other.mat[0].x) + (mat[3].y * other.mat[1].x) + (mat[3].z * other.mat[2].x) + (mat[3].w * other.mat[3].x);
	mat[3].y = (mat[3].x * other.mat[0].y) + (mat[3].y * other.mat[1].y) + (mat[3].z * other.mat[2].y) + (mat[3].w * other.mat[3].y);
	mat[3].z = (mat[3].x * other.mat[0].z) + (mat[3].y * other.mat[1].z) + (mat[3].z * other.mat[2].z) + (mat[3].w * other.mat[3].z);
	mat[3].w = (mat[3].x * other.mat[0].w) + (mat[3].y * other.mat[1].w) + (mat[3].z * other.mat[2].w) + (mat[3].w * other.mat[3].w);
	
	return *this;
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

Matrix Matrix::operator*(const Matrix& other) const
{
	return Matrix(
		// Row 1
		(mat[0].x * other.mat[0].x) + (mat[0].y * other.mat[1].x) + (mat[0].z * other.mat[2].x) + (mat[0].w * other.mat[3].x),
		(mat[0].x * other.mat[0].y) + (mat[0].y * other.mat[1].y) + (mat[0].z * other.mat[2].y) + (mat[0].w * other.mat[3].y),
		(mat[0].x * other.mat[0].z) + (mat[0].y * other.mat[1].z) + (mat[0].z * other.mat[2].z) + (mat[0].w * other.mat[3].z),
		(mat[0].x * other.mat[0].w) + (mat[0].y * other.mat[1].w) + (mat[0].z * other.mat[2].w) + (mat[0].w * other.mat[3].w),
		// Row 2
		(mat[1].x * other.mat[0].x) + (mat[1].y * other.mat[1].x) + (mat[1].z * other.mat[2].x) + (mat[1].w * other.mat[3].x),
		(mat[1].x * other.mat[0].y) + (mat[1].y * other.mat[1].y) + (mat[1].z * other.mat[2].y) + (mat[1].w * other.mat[3].y),
		(mat[1].x * other.mat[0].z) + (mat[1].y * other.mat[1].z) + (mat[1].z * other.mat[2].z) + (mat[1].w * other.mat[3].z),
		(mat[1].x * other.mat[0].w) + (mat[1].y * other.mat[1].w) + (mat[1].z * other.mat[2].w) + (mat[1].w * other.mat[3].w),
		// Row 3
		(mat[2].x * other.mat[0].x) + (mat[2].y * other.mat[1].x) + (mat[2].z * other.mat[2].x) + (mat[2].w * other.mat[3].x),
		(mat[2].x * other.mat[0].y) + (mat[2].y * other.mat[1].y) + (mat[2].z * other.mat[2].y) + (mat[2].w * other.mat[3].y),
		(mat[2].x * other.mat[0].z) + (mat[2].y * other.mat[1].z) + (mat[2].z * other.mat[2].z) + (mat[2].w * other.mat[3].z),
		(mat[2].x * other.mat[0].w) + (mat[2].y * other.mat[1].w) + (mat[2].z * other.mat[2].w) + (mat[2].w * other.mat[3].w),
		// Row 4
		(mat[3].x * other.mat[0].x) + (mat[3].y * other.mat[1].x) + (mat[3].z * other.mat[2].x) + (mat[3].w * other.mat[3].x),
		(mat[3].x * other.mat[0].y) + (mat[3].y * other.mat[1].y) + (mat[3].z * other.mat[2].y) + (mat[3].w * other.mat[3].y),
		(mat[3].x * other.mat[0].z) + (mat[3].y * other.mat[1].z) + (mat[3].z * other.mat[2].z) + (mat[3].w * other.mat[3].z),
		(mat[3].x * other.mat[0].w) + (mat[3].y * other.mat[1].w) + (mat[3].z * other.mat[2].w) + (mat[3].w * other.mat[3].w));
}

void Matrix::Multiply(const Matrix& src1, const Matrix& src2, Matrix& dst)
{
	// Row 1
	dst.mat[0].x = (src1.mat[0].x * src2.mat[0].x) + (src1.mat[0].y * src2.mat[1].x) + (src1.mat[0].z * src2.mat[2].x) + (src1.mat[0].w * src2.mat[3].x);
	dst.mat[0].y = (src1.mat[0].x * src2.mat[0].y) + (src1.mat[0].y * src2.mat[1].y) + (src1.mat[0].z * src2.mat[2].y) + (src1.mat[0].w * src2.mat[3].y);
	dst.mat[0].z = (src1.mat[0].x * src2.mat[0].z) + (src1.mat[0].y * src2.mat[1].z) + (src1.mat[0].z * src2.mat[2].z) + (src1.mat[0].w * src2.mat[3].z);
	dst.mat[0].w = (src1.mat[0].x * src2.mat[0].w) + (src1.mat[0].y * src2.mat[1].w) + (src1.mat[0].z * src2.mat[2].w) + (src1.mat[0].w * src2.mat[3].w);

	// Row 2
	dst.mat[1].x = (src1.mat[1].x * src2.mat[0].x) + (src1.mat[1].y * src2.mat[1].x) + (src1.mat[1].z * src2.mat[2].x) + (src1.mat[1].w * src2.mat[3].x);
	dst.mat[1].y = (src1.mat[1].x * src2.mat[0].y) + (src1.mat[1].y * src2.mat[1].y) + (src1.mat[1].z * src2.mat[2].y) + (src1.mat[1].w * src2.mat[3].y);
	dst.mat[1].z = (src1.mat[1].x * src2.mat[0].z) + (src1.mat[1].y * src2.mat[1].z) + (src1.mat[1].z * src2.mat[2].z) + (src1.mat[1].w * src2.mat[3].z);
	dst.mat[1].w = (src1.mat[1].x * src2.mat[0].w) + (src1.mat[1].y * src2.mat[1].w) + (src1.mat[1].z * src2.mat[2].w) + (src1.mat[1].w * src2.mat[3].w);

	// Row 3
	dst.mat[2].x = (src1.mat[2].x * src2.mat[0].x) + (src1.mat[2].y * src2.mat[1].x) + (src1.mat[2].z * src2.mat[2].x) + (src1.mat[2].w * src2.mat[3].x);
	dst.mat[2].y = (src1.mat[2].x * src2.mat[0].y) + (src1.mat[2].y * src2.mat[1].y) + (src1.mat[2].z * src2.mat[2].y) + (src1.mat[2].w * src2.mat[3].y);
	dst.mat[2].z = (src1.mat[2].x * src2.mat[0].z) + (src1.mat[2].y * src2.mat[1].z) + (src1.mat[2].z * src2.mat[2].z) + (src1.mat[2].w * src2.mat[3].z);
	dst.mat[2].w = (src1.mat[2].x * src2.mat[0].w) + (src1.mat[2].y * src2.mat[1].w) + (src1.mat[2].z * src2.mat[2].w) + (src1.mat[2].w * src2.mat[3].w);

	// Row 4
	dst.mat[3].x = (src1.mat[3].x * src2.mat[0].x) + (src1.mat[3].y * src2.mat[1].x) + (src1.mat[3].z * src2.mat[2].x) + (src1.mat[3].w * src2.mat[3].x);
	dst.mat[3].y = (src1.mat[3].x * src2.mat[0].y) + (src1.mat[3].y * src2.mat[1].y) + (src1.mat[3].z * src2.mat[2].y) + (src1.mat[3].w * src2.mat[3].y);
	dst.mat[3].z = (src1.mat[3].x * src2.mat[0].z) + (src1.mat[3].y * src2.mat[1].z) + (src1.mat[3].z * src2.mat[2].z) + (src1.mat[3].w * src2.mat[3].z);
	dst.mat[3].w = (src1.mat[3].x * src2.mat[0].w) + (src1.mat[3].y * src2.mat[1].w) + (src1.mat[3].z * src2.mat[2].w) + (src1.mat[3].w * src2.mat[3].w);
}

void Matrix::Identity()
{
	mat[0] = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
	mat[1] = Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
	mat[2] = Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
	mat[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
}

