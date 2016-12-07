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
