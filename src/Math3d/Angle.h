#pragma once

namespace Math3d
{
	struct Angle
	{
		float degrees;
		float radians;

		Angle();
		Angle(float d, float r);

		bool operator!=(const Angle& other) const;
		bool operator==(const Angle& other) const;

		Angle operator+(const Angle& other) const;
		Angle& operator+=(const Angle& other);
		Angle operator-(const Angle& other)const;
		Angle& operator-=(const Angle& other);
		Angle operator*(const float f) const;
		Angle& operator*=(const float f);

		Angle NormalizeAngle() const;

		float Sin() const;
		float SinHalfAngle() const;
		float Cos() const;
		float CosHalfAngle() const;
		float TanHalfAngle() const;

		static Angle FromDegrees(float degrees);
		static Angle FromRadians(float radians);

		static const Angle Zero;
	};
}
