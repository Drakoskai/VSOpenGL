#pragma once

#include "Matrix.h"

class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void Translate(Vector3f vector);
	void Scale(Vector3f vec);
	void RotateX(float theta);
	void RotateY(float theta);
	void RotateZ(float theta);
	Matrix& GetModelMatrix();

	Matrix m_scale;
	Matrix m_trans;
	Matrix m_rot;
	Matrix m_model;
};
