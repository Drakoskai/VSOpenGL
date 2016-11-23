#include "Geometry.h"
#include "math.h"

float Geometry::InvSqrt(const float x)
{
	return x > FloatSmallestNonDenormal ? sqrtf(1.0f / x) : INFINITY;
}
