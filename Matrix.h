#pragma once

#include "Vector.h"

struct Matrix
{
	Vector4 mat[4];

	Matrix();
	Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	Matrix(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);
	Matrix(const Matrix& other);
	
	bool Compare(const Matrix& other) const;
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
	
	Matrix& operator= (const Matrix& other);
	
	Matrix operator*(const float s) const;

	void Identity();

};