#pragma once

#include "Vector.h"
#include "Geometry.h"
#include "Angle.h"
#include "Quaternion.h"

namespace Math3d
{
	struct Matrix
	{
		Vector4f mat[4];

		Matrix();
		explicit Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		Matrix(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d);
		Matrix(const Matrix& other);
		explicit Matrix(const float src[4][4]);

		bool Compare(const Matrix& other) const;
		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;

		const Vector4f& operator[](const int index) const;
		Vector4f& operator[](const int index);

		Matrix& operator*=(const Matrix& other);

		Matrix& operator= (const Matrix& other);
		Matrix operator*(const float s) const;
		Matrix operator*(const Matrix& other) const;
		Vector4f operator*(const Vector4f& other) const;
		Vector3f Matrix::operator*(const Vector3f& vec) const;

		operator const float* () const
		{
			return static_cast<const float*>(&mat[0].x);
		}

		operator float* ()
		{
			return static_cast<float*>(&mat[0].x);
		}

		friend std::ostream& operator << (std::ostream& os, const Matrix& m) {
			return os << std::endl
				<< m[0] << std::endl
				<< m[1] << std::endl
				<< m[2] << std::endl;
		}

		friend std::istream& operator >> (std::istream& is, Matrix& m)
		{
			return is >> m.mat[0] >> m.mat[1] >> m.mat[2];
		}

		void Identity();
		void Zero();
	};

	inline Matrix MakeTranslate(const float x, const float y, const float z)
	{
		return Matrix{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x, y, z, 1.0f };
	}

	inline Matrix MakeTranslate(const Vector3f& vector)
	{
		return MakeTranslate(vector.x, vector.y, vector.z);
	}

	inline Matrix MakeTranslate(const Vector4f& vector)
	{
		return MakeTranslate(vector.x, vector.y, vector.z);
	}

	inline Matrix MakeScale(const float x, const float y, const float z)
	{
		return Matrix{
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };
	}

	inline Matrix MakeScale(const Vector3f& scale)
	{
		return MakeScale(scale.x, scale.y, scale.z);
	}

	inline Matrix MakeScale(const Vector4f& scale)
	{
		return MakeScale(scale.x, scale.y, scale.z);
	}

	inline Matrix MakePerspectiveRH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		float tanHalfFovy = fieldOfView.TanHalfAngle();
		float zRange = zFar - zNear;

		return Matrix{
			1.0f / (screenAspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
			0.0f, 0.0f, -(zFar + zNear) / zRange, -1.0f,
			0.0f, 0.0f, -(2.0f * zFar * zNear) / zRange, 0.0f };
	}

	inline Matrix MakePerspectiveLH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		float tanHalfFovy = fieldOfView.TanHalfAngle();
		float zRange = zFar - zNear;

		return Matrix{
			1.0f / (screenAspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
			0.0f, 0.0f, -(zFar + zNear) / zRange, 1.0f,
			0.0f, 0.0f, -(2.0f * zFar * zNear) / zRange, 0.0f };
	}

	inline Matrix MakePerspective(const float fieldOfView, const float screenAspect, const float zNear, const float zFar)
	{
		return MakePerspectiveRH(Angle::FromDegrees(fieldOfView), screenAspect, zNear, zFar);
	}

	inline Matrix MakeOrtho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
	{
		return Matrix(
			2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
			0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
			0.0f, 0.0f, 2.0f / (zNear - zFar), -(zFar + zNear) / (zFar - zNear),
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline Matrix MakeRotationX(const float theta)
	{
		float angle = Geometry::DegToRad * theta;

		Matrix matrix;
		matrix[2][2] = matrix[1][1] = cos(angle);
		matrix[2][1] = sin(angle);
		matrix[1][2] = -matrix[2][1];

		return matrix;
	}

	inline Matrix MakeRotationY(const float theta)
	{
		float angle = Geometry::DegToRad * theta;

		Matrix matrix;
		matrix[2][2] = matrix[0][0] = cos(angle);
		matrix[0][2] = sin(angle);
		matrix[2][0] = -matrix[0][2];

		return matrix;
	}

	inline Matrix MakeRotationZ(const float theta)
	{
		float angle = Geometry::DegToRad * theta;

		Matrix matrix;
		matrix[0][0] = matrix[1][1] = cosf(angle);
		matrix[1][0] = sinf(angle);
		matrix[0][1] = -matrix[1][0];

		return matrix;
	}

	inline Matrix MakeRotation(const Quaternion& rot)
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

	inline Matrix MakeLookAtRH(Vector4f eye, Vector4f lookAt, Vector4f up)
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

	inline Matrix MakeLookAtLH(Vector4f eye, Vector4f lookAt, Vector4f up)
	{
		Vector4f zAxis = Normalize(lookAt - eye);
		Vector4f xAxis = Normalize(Cross(up, zAxis));
		Vector4f yAxis = Normalize(Cross(zAxis, xAxis));

		Matrix view = {
			Vector4f(xAxis.x, yAxis.x, zAxis.x, 0.0f),
			Vector4f(xAxis.y, yAxis.y, zAxis.y, 0.0f),
			Vector4f(xAxis.z, yAxis.z, zAxis.z, 0.0f),
			Vector4f(-Dot(xAxis, eye), -Dot(yAxis, eye), -Dot(zAxis, eye), 1.0f) };

		return view;
	}
}
