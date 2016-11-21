#pragma once
#include "Plane.h"

struct Matrix;

struct Frustum
{
	Plane left;
	Plane right;
	Plane bottom;
	Plane top;
	Plane near;
	Plane far;

	Frustum(float width, float hieght, int viewportWidth, int viewPortHeight);

};
