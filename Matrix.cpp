#include "Matrix.h"

Matrix::Matrix()
{
	mat[0] = 1.0f; mat[1] = 0.0f; mat[2] = 0.0f; mat[3] = 0.0f;
	mat[4] = 0.0f; mat[5] = 1.0f; mat[6] = 0.0f; mat[7] = 0.0f;
	mat[8] = 0.0f; mat[9] = 0.0f; mat[10] = 1.0f; mat[11] = 0.0f;
	mat[12] = 0.0f; mat[13] = 0.0f; mat[14] = 0.0f; mat[15] = 1.0f;
}

Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	mat[0] = m00; mat[1] = m01; mat[2] = m02; mat[3] = m03;
	mat[0] = m10; mat[1] = m11; mat[2] = m12; mat[3] = m13;
	mat[0] = m20; mat[1] = m21; mat[2] = m22; mat[3] = m23;
	mat[0] = m30; mat[1] = m31; mat[2] = m32; mat[3] = m33;
}

Matrix::Matrix(const Matrix& other)
{
	memcpy(mat, other.mat, 16 * sizeof(float));
}

bool Matrix::Compare(const Matrix& other) const
{
	for (int i = 0; i < 16; i++) {
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

Matrix& Matrix::operator*=(const Matrix& b)
{
	float b00 = b.mat[0 + 0 * 4];
	float b10 = b.mat[1 + 0 * 4];
	float b20 = b.mat[2 + 0 * 4];
	float b30 = b.mat[3 + 0 * 4];
	float b01 = b.mat[0 + 1 * 4];
	float b11 = b.mat[1 + 1 * 4];
	float b21 = b.mat[2 + 1 * 4];
	float b31 = b.mat[3 + 1 * 4];
	float b02 = b.mat[0 + 2 * 4];
	float b12 = b.mat[1 + 2 * 4];
	float b22 = b.mat[2 + 2 * 4];
	float b32 = b.mat[3 + 2 * 4];
	float b03 = b.mat[0 + 3 * 4];
	float b13 = b.mat[1 + 3 * 4];
	float b23 = b.mat[2 + 3 * 4];
	float b33 = b.mat[3 + 3 * 4];

	float ai0 = mat[0 * 4];
	float ai1 = mat[1 * 4];
	float ai2 = mat[2 * 4];
	float ai3 = mat[3 * 4];
	mat[0 * 4] = static_cast<float>(ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30);
	mat[1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	mat[2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	mat[3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = mat[1 + 0 * 4];
	ai1 = mat[1 + 1 * 4];
	ai2 = mat[1 + 2 * 4];
	ai3 = mat[1 + 3 * 4];
	mat[1 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	mat[1 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	mat[1 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	mat[1 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = mat[2 + 0 * 4];
	ai1 = mat[2 + 1 * 4];
	ai2 = mat[2 + 2 * 4];
	ai3 = mat[2 + 3 * 4];
	mat[2 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	mat[2 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	mat[2 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	mat[2 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = mat[3 + 0 * 4];
	ai1 = mat[3 + 1 * 4];
	ai2 = mat[3 + 2 * 4];
	ai3 = mat[3 + 3 * 4];
	mat[3 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	mat[3 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	mat[3 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	mat[3 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	return *this;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	memcpy(mat, other.mat, 16 * sizeof(float));

	return *this;
}

Matrix Matrix::operator*(const float s) const
{
	return Matrix(
		mat[0] * s, mat[1] * s, mat[2] * s, mat[3] * s,
		mat[4] * s, mat[5] * s, mat[6] * s, mat[7] * s,
		mat[8] * s, mat[9] * s, mat[10] * s, mat[11] * s,
		mat[12] * s, mat[13] * s, mat[14] * s, mat[15] * s);
}

Matrix Matrix::operator*(const Matrix& b) const
{
	float b00 = b.mat[0 + 0 * 4];
	float b10 = b.mat[1 + 0 * 4];
	float b20 = b.mat[2 + 0 * 4];
	float b30 = b.mat[3 + 0 * 4];
	float b01 = b.mat[0 + 1 * 4];
	float b11 = b.mat[1 + 1 * 4];
	float b21 = b.mat[2 + 1 * 4];
	float b31 = b.mat[3 + 1 * 4];
	float b02 = b.mat[0 + 2 * 4];
	float b12 = b.mat[1 + 2 * 4];
	float b22 = b.mat[2 + 2 * 4];
	float b32 = b.mat[3 + 2 * 4];
	float b03 = b.mat[0 + 3 * 4];
	float b13 = b.mat[1 + 3 * 4];
	float b23 = b.mat[2 + 3 * 4];
	float b33 = b.mat[3 + 3 * 4];
	Matrix a;
	float ai0 = mat[0 * 4];
	float ai1 = mat[1 * 4];
	float ai2 = mat[2 * 4];
	float ai3 = mat[3 * 4];
	a.mat[0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	a.mat[1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	a.mat[2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	a.mat[3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = mat[1 + 0 * 4];
	ai1 = mat[1 + 1 * 4];
	ai2 = mat[1 + 2 * 4];
	ai3 = mat[1 + 3 * 4];
	a.mat[1 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	a.mat[1 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	a.mat[1 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	a.mat[1 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = mat[2 + 0 * 4];
	ai1 = mat[2 + 1 * 4];
	ai2 = mat[2 + 2 * 4];
	ai3 = mat[2 + 3 * 4];
	a.mat[2 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	a.mat[2 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	a.mat[2 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	a.mat[2 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = mat[3 + 0 * 4]; // row-3 of a
	ai1 = mat[3 + 1 * 4];
	ai2 = mat[3 + 2 * 4];
	ai3 = mat[3 + 3 * 4];
	a.mat[3 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	a.mat[3 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	a.mat[3 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	a.mat[3 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	return a;
}

void Matrix::MakeScale(float x, float y, float z)
{
	mat[0] = x;
	mat[5] = y;
	mat[10] = z;
	mat[15] = 1.0f;
}

Matrix Matrix::MakePerspective(float fieldOfView, float screenAspect, float screenNear, float screenDepth)
{
	return Matrix(
		1.0f / (screenAspect * tan(fieldOfView * 0.5f)), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / tan(fieldOfView * 0.5f), 0.0f, 0.0f,
		0.0f, 0.0f, screenDepth / (screenDepth - screenNear), 0.0f,
		0.0f, 0.0f, -screenNear * screenDepth / (screenDepth - screenNear), 0.0f);
}

Matrix Matrix::MakeLookAt(Vector3f eye, Vector3f lookAt, Vector3f up)
{
	Vector3f zAxis = lookAt - eye;
	zAxis.Normalize();

	Vector3f xAxis = zAxis;
	xAxis.Cross(up).Normalize();

	Vector3f yAxis = zAxis;
	yAxis.Cross(xAxis).Normalize();

	return Matrix(
		xAxis.x, yAxis.x, zAxis.x, 0.0f,
		xAxis.y, yAxis.y, zAxis.y, 0.0f,
		xAxis.z, yAxis.z, zAxis.z, 0.0f,
		xAxis.Dot(eye) * -1.0f, yAxis.Dot(eye)* -1.0f, zAxis.Dot(eye) * -1.0f, 1.0f);

}

void Matrix::Multiply(const Matrix& a, const Matrix& b, Matrix& d)
{
	float b00 = b.mat[0 + 0 * 4];
	float b10 = b.mat[1 + 0 * 4];
	float b20 = b.mat[2 + 0 * 4];
	float b30 = b.mat[3 + 0 * 4];
	float b01 = b.mat[0 + 1 * 4];
	float b11 = b.mat[1 + 1 * 4];
	float b21 = b.mat[2 + 1 * 4];
	float b31 = b.mat[3 + 1 * 4];
	float b02 = b.mat[0 + 2 * 4];
	float b12 = b.mat[1 + 2 * 4];
	float b22 = b.mat[2 + 2 * 4];
	float b32 = b.mat[3 + 2 * 4];
	float b03 = b.mat[0 + 3 * 4];
	float b13 = b.mat[1 + 3 * 4];
	float b23 = b.mat[2 + 3 * 4];
	float b33 = b.mat[3 + 3 * 4];

	float ai0 = a.mat[0 * 4];
	float ai1 = a.mat[1 * 4];
	float ai2 = a.mat[2 * 4];
	float ai3 = a.mat[3 * 4];
	d.mat[0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	d.mat[1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	d.mat[2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	d.mat[3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = a.mat[1 + 0 * 4];
	ai1 = a.mat[1 + 1 * 4];
	ai2 = a.mat[1 + 2 * 4];
	ai3 = a.mat[1 + 3 * 4];
	d.mat[1 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	d.mat[1 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	d.mat[1 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	d.mat[1 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = a.mat[2 + 0 * 4];
	ai1 = a.mat[2 + 1 * 4];
	ai2 = a.mat[2 + 2 * 4];
	ai3 = a.mat[2 + 3 * 4];
	d.mat[2 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	d.mat[2 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	d.mat[2 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	d.mat[2 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;

	ai0 = a.mat[3 + 0 * 4];
	ai1 = a.mat[3 + 1 * 4];
	ai2 = a.mat[3 + 2 * 4];
	ai3 = a.mat[3 + 3 * 4];
	d.mat[3 + 0 * 4] = ai0 * b00 + ai1 * b10 + ai2 * b20 + ai3 * b30;
	d.mat[3 + 1 * 4] = ai0 * b01 + ai1 * b11 + ai2 * b21 + ai3 * b31;
	d.mat[3 + 2 * 4] = ai0 * b02 + ai1 * b12 + ai2 * b22 + ai3 * b32;
	d.mat[3 + 3 * 4] = ai0 * b03 + ai1 * b13 + ai2 * b23 + ai3 * b33;
}

void Matrix::Identity()
{
	mat[0] = 1.0f; mat[1] = 0.0f; mat[2] = 0.0f; mat[3] = 0.0f;
	mat[4] = 0.0f; mat[5] = 1.0f; mat[6] = 0.0f; mat[7] = 0.0f;
	mat[8] = 0.0f; mat[9] = 0.0f; mat[10] = 1.0f; mat[11] = 0.0f;
	mat[12] = 0.0f; mat[13] = 0.0f; mat[14] = 0.0f; mat[15] = 1.0f;
}

void Matrix::Zero()
{
	mat[0] = 0.0f; mat[1] = 0.0f; mat[2] = 0.0f; mat[3] = 0.0f;
	mat[4] = 0.0f; mat[5] = 0.0f; mat[6] = 0.0f; mat[7] = 0.0f;
	mat[8] = 0.0f; mat[9] = 0.0f; mat[10] = 0.0f; mat[11] = 0.0f;
	mat[12] = 0.0f; mat[13] = 0.0f; mat[14] = 0.0f; mat[15] = 0.0f;
}
