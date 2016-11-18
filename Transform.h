#pragma once

#include "Matrix.h"

/**
 * Component that controls the movement of an object
 * in 3d space.
 */
class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void Translate(Vector3 vector);
	void Translate(float x, float y, float z);
	void Scale(float factor);
	void Scale(float h, float w, float d);
	void Rotate(float angle, Vector3 axis);
	void Rotate(float angle, float x, float y, float z);

private:
	Matrix translationMatrix;
	Matrix rotationMatrix;
};
