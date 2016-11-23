#pragma once

#include "Plane.h"

struct Frustum
{
	Plane leftPlane;
	Plane rightPlane;
	Plane bottomPlane;
	Plane topPlane;
	Plane nearPlane;
	Plane farPlane;

	Frustum();
	Frustum(float fieldOfView, int width, int height, float nearClip, float farClip);
};
