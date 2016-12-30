#pragma once

#include "Vector.h"
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
		Vector3f operator*(const Vector3f& vec) const;

		operator const float*() const;
		operator float*();

		friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
		friend std::istream& operator>>(std::istream& is, Matrix& m);

		void Identity();
		void Zero();
	};

	Matrix MakeTranslate(const float x, const float y, const float z);
	Matrix MakeTranslate(const Vector3f& vector);
	Matrix MakeTranslate(const Vector4f& vector);
	
	Matrix MakeScale(const float x, const float y, const float z);
	Matrix MakeScale(const Vector3f& scale);
	Matrix MakeScale(const Vector4f& scale);
	
	Matrix MakePerspectiveOGLRH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar);
	Matrix MakePerspectiveOGLLH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar);
	
	Matrix MakePerspectiveDXRH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar);
	Matrix MakePerspectiveDXLH(const Angle& fieldOfView, const float screenAspect, const float zNear, const float zFar);


	Matrix MakeRotationX(const float theta);
	Matrix MakeRotationY(const float theta);
	Matrix MakeRotationZ(const float theta);
	
	Matrix MakeRotation(const Quaternion& rot);
	Matrix MakeLookAtRH(Vector3f eye, Vector3f lookAt, Vector3f up);
	Matrix MakeLookAtLH(Vector3f eye, Vector3f lookAt, Vector3f up);
}
