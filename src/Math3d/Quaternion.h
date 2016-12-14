#pragma once

#include "Angle.h"
#include "Vector.h"
#include "Geometry.h"

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
		Vector4f GetAxis() const;

		Angle GetRotationX() const;
		Angle GetRotationY() const;
		Angle GetRotationZ() const;

		Vector4f GetUp() const;
		Vector4f GetRight() const;
		Vector4f GetForward() const;

		static Quaternion FromAxisAngle(const Angle& angle, const float x, const float y, const float z);
		static Quaternion FromAxisAngle(const Angle& angle, const Vector4f& axis);
		static Quaternion FromAxisAngle(const Angle& angle, const Vector3f& axis);
		static Quaternion FromRotationEuler(const Angle& x, const Angle& y, const Angle& z);
		static Quaternion FromMatrix(const Matrix& m);
		static Quaternion MakeLookAt(Vector4f sourcePoint, Vector4f destPoint);

		static const Quaternion Identity;
		static const Quaternion Zero;
	};

	static Quaternion Cross(const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion{
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x };
	}

	static Quaternion Normalize(const Quaternion& q)
	{
		float length = q.Length();
		if (length != 0.0f && length != -0.0f)
		{
			float ilength;
			ilength = 1 / length;
			return Quaternion{ q.x / ilength, q.y / ilength, q.z / ilength, q.w / ilength };
		}

		return Quaternion{ q.x, q.y, q.z, q.w };
	}
}
