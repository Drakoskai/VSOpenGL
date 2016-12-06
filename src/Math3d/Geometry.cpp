#include "../pch.h"
#include "Geometry.h"

namespace Math3d
{
	float Geometry::InvSqrt(const float x)
	{
		return x > FloatSmallestNonDenormal ? sqrtf(1.0f / x) : INFINITY;
	}
}
