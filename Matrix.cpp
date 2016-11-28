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

Matrix Matrix::MakeScale(float x, float y, float z)
{
	Matrix m;
	m.mat[0][0] = x;
	m.mat[1][1] = y;
	m.mat[2][2] = z;
	m.mat[3][3] = 1.0f;
	
	return m;
}

Matrix Matrix::MakePerspective(float fieldOfView, float screenAspect, float screenNear, float screenFar)
{
	float const a = 1.0f / static_cast<float>(tan(fieldOfView / 2.0f));

	return Matrix(
		a / screenAspect, 0.0f, 0.0f, 0.0f,
		0.0f, a, 0.0f, 0.0f,
		0.0f, 0.0f, -((screenFar + screenNear) / (screenFar - screenNear)), -1.0f,
		0.0f, 0.0f, -((2.0f * screenFar * screenNear) / (screenFar - screenNear)), 0.0f);
}

Matrix Matrix::MakeOrtho(float l, float r, float b, float t, float n, float f)
{
	Matrix m = Matrix(
		2.0f / l, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / r, 0.0f, 0.0f,
		0.0f, 0.0f, -2.0f / (f - n), -(f + n) / (f - n),
		0.0f, 0.0f, 0.0f, 1.0f);

	return m;
}

Matrix Matrix::MakeRotationZ(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	Matrix R = Matrix(
		c, -s, 0.f, 0.f,
		s, c, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

	return R;
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

void Matrix::Multiply(const Matrix& a, const Matrix& b, Matrix& dst)
{
	const float *m1Ptr = reinterpret_cast<const float *>(&a);
	const float *m2Ptr = reinterpret_cast<const float *>(&b);
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
