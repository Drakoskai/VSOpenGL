#include "pch.h"
#include "Plane.h"

Plane::Plane(): n(Vector4f::Zero) { }

Plane::Plane(Vector4f vec) : n(vec) { }

Plane::Plane(float nx, float ny, float nz, float d)
	: n(nx, ny, nz, d) { }
