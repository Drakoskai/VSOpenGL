#pragma once

namespace Math3d
{
	namespace Geometry
	{
		static const int IEEFloatMantissaBits = 23;
		static const float SmallestNonDenormal = 1 << IEEFloatMantissaBits;
		static const float FloatSmallestNonDenormal = *reinterpret_cast<const float *>(&SmallestNonDenormal);

		static const float PI = 3.14159265358979323846f;
		static const float DegToRad = PI / 180.0f;
		static const float RadToDeg = 180.0f / PI;
		static const float Infinity = 1e30f;


		float InvSqrt(const float x);
	}
}