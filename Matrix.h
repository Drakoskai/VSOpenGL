#pragma once

#include "Vector.h"

struct Matrix
{
	float mat[16];

	Matrix();
	Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	Matrix(const Matrix& other);
	
	bool Compare(const Matrix& other) const;
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;

	Matrix& operator*=(const Matrix& other);

	Matrix& operator= (const Matrix& other);
	Matrix operator*(const float s) const;
	Matrix operator*(const Matrix& other) const;
	void MakeScale(float x, float y, float z);
	static Matrix MakePerspective(float fieldOfView, float screenAspect, float screenNear, float screenDepth);
	static Matrix MakeLookAt(Vector3f eye, Vector3f lookAt, Vector3f up);
	static void Multiply(const Matrix& src1, const Matrix& src2, Matrix& dst);

	void Identity();
	void Zero();

};

