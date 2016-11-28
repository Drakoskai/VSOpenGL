#pragma once

#include "Vector.h"

struct Matrix
{
	Vector4f mat[4];

	Matrix();
	explicit Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
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
	static Matrix MakeScale(float x, float y, float z);
	static Matrix MakePerspective(float fieldOfView, float screenAspect, float screenNear, float screenDepth);
	static Matrix MakeOrtho(float l, float r, float b, float t, float n, float f);
	static Matrix MakeRotationZ(float angle);
	static Matrix MakeLookAt(Vector3f eye, Vector3f lookAt, Vector3f up);
	static void Multiply(const Matrix& src1, const Matrix& src2, Matrix& dst);

	void Identity();
	void Zero();

};

