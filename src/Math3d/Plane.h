#pragma once

#include "Vector.h"

namespace Math3d
{
	struct Plane
	{
		Vector4f n;

		Plane();
		Plane(Vector4f vec);
		Plane(float nx, float ny, float nz, float d);

	};
}
