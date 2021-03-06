#include "../pch.h"
#include "Matrix.h"
#include "Geometry.h"

namespace Math3d
{
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
		const float* ptr1 = reinterpret_cast<const float*>(mat);
		const float* ptr2 = reinterpret_cast<const float*>(other.mat);
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
		return Matrix{
			mat[0].x * s, mat[0].y * s, mat[0].z * s, mat[0].w * s,
			mat[1].x * s, mat[1].y * s, mat[1].z * s, mat[1].w * s,
			mat[2].x * s, mat[2].y * s, mat[2].z * s, mat[2].w * s,
			mat[3].x * s, mat[3].y * s, mat[3].z * s, mat[3].w * s };
	}

	Matrix Matrix::operator*(const Matrix& other) const
	{

		Vector4f X = other * mat[0];
		Vector4f Y = other * mat[1];
		Vector4f Z = other * mat[2];
		Vector4f W = other * mat[3];

		return Matrix{ X, Y, Z, W };
	}

	Vector4f Matrix::operator*(const Vector4f& v) const
	{
		return Vector4f{
			mat[0][0] * v.x + mat[1][0] * v.y + mat[2][0] * v.z + mat[3][0] * v.w,
			mat[0][1] * v.x + mat[1][1] * v.y + mat[2][1] * v.z + mat[3][1] * v.w,
			mat[0][2] * v.x + mat[1][2] * v.y + mat[2][2] * v.z + mat[3][2] * v.w,
			mat[0][3] * v.x + mat[1][3] * v.y + mat[2][3] * v.z + mat[3][3] * v.w };
	}

	Vector3f Matrix::operator*(const Vector3f& vec) const
	{

		float s = mat[3].x * vec.x + mat[3].y * vec.y + mat[3].z * vec.z + mat[3].w;
		if (s == 0.0f) {
			return Vector3f::Zero;
		}
		if (s == 1.0f) {
			return Vector3f{
				mat[0].x * vec.x + mat[0].y * vec.y + mat[0].z * vec.z + mat[0].w,
				mat[1].x * vec.x + mat[1].y * vec.y + mat[1].z * vec.z + mat[1].w,
				mat[2].x * vec.x + mat[2].y * vec.y + mat[2].z * vec.z + mat[2].w };
		}

		float invS = 1.0f / s;

		return Vector3f{
			(mat[0].x * vec.x + mat[0].y * vec.y + mat[0].z * vec.z + mat[0].w) * invS,
			(mat[1].x * vec.x + mat[1].y * vec.y + mat[1].z * vec.z + mat[1].w) * invS,
			(mat[2].x * vec.x + mat[2].y * vec.y + mat[2].z * vec.z + mat[2].w) * invS };
	}

	Matrix::operator const float*() const
	{
		return static_cast<const float*>(&mat[0].x);
	}

	Matrix::operator float*()
	{
		return static_cast<float*>(&mat[0].x);
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

	Matrix MakeTranslate(const float x, const float y, const float z)
	{
		return Matrix{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x, y, z, 1.0f };
	}

	Matrix MakeTranslate(const Vector3f& vector)
	{
		return MakeTranslate(vector.x, vector.y, vector.z);
	}

	Matrix MakeTranslate(const Vector4f& vector)
	{
		return MakeTranslate(vector.x, vector.y, vector.z);
	}

	Matrix MakeScale(const float x, const float y, const float z)
	{
		return Matrix{
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix MakeScale(const Vector3f& scale)
	{
		return MakeScale(scale.x, scale.y, scale.z);
	}

	Matrix MakeScale(const Vector4f& scale)
	{
		return MakeScale(scale.x, scale.y, scale.z);
	}

	Matrix MakePerspectiveOGLRH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		float tanHalfFovy = fieldOfView.TanHalfAngle();
		float zRange = zFar - zNear;

		return Matrix{
			1.0f / (screenAspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
			0.0f, 0.0f, -(zFar + zNear) / zRange, -1.0f,
			0.0f, 0.0f, -(2.0f * zFar * zNear) / zRange, 0.0f };
	}

	Matrix MakePerspectiveOGLLH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		float tanHalfFovy = fieldOfView.TanHalfAngle();
		float zRange = zFar - zNear;

		return Matrix{
			1.0f / (screenAspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
			0.0f, 0.0f, -(zFar + zNear) / zRange, 1.0f,
			0.0f, 0.0f, 2.0f * zFar * zNear / zRange, 0.0f };
	}

	Matrix MakePerspectiveDXRH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		float tanHalfFovy = fieldOfView.TanHalfAngle();
		float zRange = zFar - zNear;

		return Matrix{
			screenAspect * 1.0f / tanHalfFovy, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
			0.0f, 0.0f, zFar / zRange, -1.0f,
			0.0f, 0.0f, zNear * (zFar / zRange), 0.0f };
	}

	Matrix MakePerspectiveDXLH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		float tanHalfFovy = fieldOfView.TanHalfAngle();
		float zRange = zFar - zNear;

		return Matrix{
			screenAspect * 1.0f / tanHalfFovy, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
			0.0f, 0.0f, zFar / zRange, 1.0f,
			0.0f, 0.0f, -zNear * (zFar / zRange), 0.0f };
	}

	Matrix MakeRotationX(const float theta)
	{
		return MakeRotation(Quaternion::FromAxisAngle(Angle::FromDegrees(theta), Vector4f::UnitX));
	}

	Matrix MakeRotationY(const float theta)
	{
		return MakeRotation(Quaternion::FromAxisAngle(Angle::FromDegrees(theta), Vector4f::UnitY));
	}
	
	Matrix MakeRotationZ(const float theta)
	{
		return MakeRotation(Quaternion::FromAxisAngle(Angle::FromDegrees(theta), Vector4f::UnitZ));
	}

	Matrix MakeRotation(const Quaternion& rot)
	{
		return Matrix{
			1.0f - 2.0f * rot.y * rot.y - 2.0f * rot.z * rot.z,
			2.0f * rot.x * rot.y - 2.0f * rot.w * rot.z,
			2.0f * rot.x * rot.z + 2.0f * rot.w * rot.y, 0.0f,
			2.0f * rot.x * rot.y + 2.0f * rot.w * rot.z,
			1.0f - 2.0f * rot.x * rot.x - 2.0f * rot.z * rot.z,
			2.0f * rot.y * rot.z - 2.0f * rot.w * rot.x, 0.0f,
			2.0f * rot.x * rot.z - 2.0f * rot.w * rot.y,
			2.0f * rot.y * rot.z + 2.0f * rot.x * rot.w,
			1.0f - 2.0f * rot.x * rot.x - 2.0f * rot.y * rot.y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix MakeLookAtRH(Vector3f eye, Vector3f lookAt, Vector3f up)
	{
		Vector4f zAxis = Normalize(eye - lookAt);
		Vector4f xAxis = Normalize(Cross(up, zAxis));
		Vector4f yAxis = Normalize(Cross(zAxis, xAxis));

		Matrix view = {
			Vector4f(xAxis.x, yAxis.x, zAxis.x, 0.0f),
			Vector4f(xAxis.y, yAxis.y, zAxis.y, 0.0f),
			Vector4f(xAxis.z, yAxis.z, zAxis.z, 0.0f),
			Vector4f(-Dot(xAxis, eye), -Dot(yAxis, eye), -Dot(zAxis, eye), 1.0f) };

		return view;
	}

	Matrix MakeLookAtLH(Vector3f eye, Vector3f lookAt, Vector3f up)
	{
		Vector4f zAxis = Normalize(lookAt - eye);
		Vector4f xAxis = Normalize(Cross(up, zAxis));
		Vector4f yAxis = Normalize(Cross(zAxis, xAxis));

		Matrix view = {
			Vector4f(xAxis.x, yAxis.x, zAxis.x, 0.0f),
			Vector4f(xAxis.y, yAxis.y, zAxis.y, 0.0f),
			Vector4f(xAxis.z, yAxis.z, zAxis.z, 0.0f),
			Vector4f(Dot(xAxis, eye), Dot(yAxis, eye), Dot(zAxis, eye), 1.0f) };

		return view;
	}

	std::ostream& operator<<(std::ostream& os, const Matrix& m)
	{
		return os << std::endl << m[0] << std::endl << m[1] << std::endl << m[2] << std::endl;
	}

	std::istream& operator>>(std::istream& is, Matrix& m)
	{
		return is >> m.mat[0] >> m.mat[1] >> m.mat[2];
	}
}
