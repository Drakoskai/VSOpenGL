#include "../pch.h"
#include "Angle.h"
#include "Geometry.h"

namespace Math3d
{
	Angle::Angle() : degrees(0.0f), radians(0.0f) { }

	Angle::Angle(float d, float r) : degrees(d), radians(r) { }

	bool Angle::operator!=(const Angle& other) const
	{
		return other.degrees != degrees;
	}

	bool Angle::operator==(const Angle& other) const
	{
		return other.degrees == degrees;
	}

	float Angle::Sin() const
	{
		return sinf(radians);
	}

	float Angle::SinHalfAngle() const
	{
		return sinf(0.5f * radians);
	}

	float Angle::Cos() const
	{
		return cosf(radians);
	}

	float Angle::CosHalfAngle() const
	{
		return cosf(0.5f * radians);
	}

	float Angle::TanHalfAngle() const
	{
		return tan(0.5f * radians);
	}

	Angle Angle::FromDegrees(float degrees)
	{
		return Angle(degrees, Geometry::DegToRad * degrees);
	}

	Angle Angle::FromRadians(float radians)
	{
		return Angle(Geometry::RadToDeg * radians, radians);
	}
}
