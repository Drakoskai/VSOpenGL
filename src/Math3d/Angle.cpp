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

	Angle Angle::operator+(const Angle& other) const
	{
		return FromDegrees(degrees + other.degrees);
	}

	Angle& Angle::operator+=(const Angle& other)
	{
		degrees += other.degrees;
		return *this;
	}

	Angle Angle::operator-(const Angle& other) const
	{
		return FromDegrees(degrees - other.degrees);
	}

	Angle& Angle::operator-=(const Angle& other)
	{
		degrees -= other.degrees;
		return *this;
	}

	Angle Angle::operator*(const float f) const
	{
		return FromDegrees(degrees * f);
	}

	Angle& Angle::operator*=(const float f)
	{
		degrees *= f;
		return *this;
	}

	Angle Angle::NormalizeAngle() const
	{
		float a = fmod(degrees, 360.0f);
		float d = a > 180.0f ? a - 360.0f : a < -180.0f ? 360.0f + a : a;

		return FromDegrees(d);
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
		return tanf(0.5f * radians);
	}

	Angle Angle::FromDegrees(float degrees)
	{
		return Angle(degrees, Geometry::DegToRad * degrees);
	}

	Angle Angle::FromRadians(float radians)
	{
		return Angle(Geometry::RadToDeg * radians, radians);
	}

	const Angle Angle::Zero = FromDegrees(0.0f);
}
