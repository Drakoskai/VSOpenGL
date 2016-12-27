#pragma once

#include "Angle.h"
#include "Vector.h"

namespace Math3d
{
	struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;

		Quaternion();
		Quaternion(float x_, float y_, float z_, float w_);

		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator*(const float s) const;
		Quaternion operator/(const Quaternion& other) const;
		Quaternion operator/(const float s) const;

		Quaternion& operator*=(const Quaternion& other);

		operator float*();
		operator const float*() const;

		friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion);
		friend std::istream& operator>>(std::istream& is, Quaternion& quaternion);

		float Length() const;
		Quaternion Inverse() const;

		Angle GetAngle() const;
		Vector3f GetAxis() const;

		Angle GetRotationX() const;
		Angle GetRotationY() const;
		Angle GetRotationZ() const;

		Vector3f GetUp() const;
		Vector3f GetRight() const;
		Vector3f GetForward() const;

		static Quaternion FromAxisAngle(const Angle& angle, const float x, const float y, const float z);
		static Quaternion FromAxisAngle(const Angle& angle, const Vector4f& axis);
		static Quaternion FromAxisAngle(const Angle& angle, const Vector3f& axis);
		static Quaternion FromRotationEuler(const Angle& x, const Angle& y, const Angle& z);
		static Quaternion FromMatrix(const Matrix& m);
		static Quaternion MakeLookAt(Vector4f sourcePoint, Vector4f destPoint);

		static const Quaternion Identity;
		static const Quaternion Zero;
	};

	static Quaternion Cross(const Quaternion& q1, const Quaternion& q2);
	static Quaternion Normalize(const Quaternion& q);
}
