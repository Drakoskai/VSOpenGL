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
		float Cos() const;

		static Angle FromDegrees(float degrees);
		static Angle FromRadians(float radians);
	};
}
