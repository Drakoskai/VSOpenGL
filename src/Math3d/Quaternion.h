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

		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f){ }
		Quaternion(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) { }

		bool operator==(const Quaternion& other) const
		{
			if (x == other.x && y == other.y && z == other.z && w == other.w)
			{
				return true;
			}

			return false;
		}

		bool operator!=(const Quaternion& other) const
		{
			if (x == other.x && y == other.y && z == other.z && w == other.w)
			{
				return false;
			}

			return true;
		}

		Quaternion operator*(const Quaternion& other) const
		{
			return Quaternion(
				w * other.x + x * other.w + y * other.z - z * other.y,
				w * other.y + y * other.w + z * other.x - x * other.z,
				w * other.z + z * other.w + x * other.y - y * other.x,
				w * other.w - x * other.x - y * other.y - z * other.z);
		}

		float Length() const
		{
			float len = x * x + y * y + z * z + w * w;
			return sqrtf(len);
		}

		Quaternion Normalize() const
		{
			float length = Length();
			if (length)
			{
				float ilength;
				ilength = 1 / length;
				return Quaternion(x / ilength, y / ilength, z / ilength, w / ilength);
			}

			return Quaternion(x, y, z, w);
		}


		static Quaternion FromAxisAngle(const Angle& angle, const float x, const float y, const float z)
		{
			float s = angle.SinHalfAngle();
			float c = angle.CosHalfAngle();

			float xAxis = x;
			float yAxis = y;
			float zAxis = z;

			float length = sqrtf(x * x + y * y + z * z);
			if (length != 0.0f && (length != 1.0f))
			{
				xAxis /= length;
				yAxis /= length;
				zAxis /= length;
			}

			return Quaternion(xAxis * s, yAxis * s, zAxis * s, c);
		}

		static Quaternion FromAxisAngle(const Angle& angle, const Vector3f& axis)
		{
			return FromAxisAngle(angle, axis.x, axis.y, axis.z);
		}

		static Quaternion FromRotationEuler(const Angle& x, const Angle& y, const Angle& z)
		{
			float cx = x.CosHalfAngle();
			float cy = y.CosHalfAngle();
			float cz = z.CosHalfAngle();
			float sx = x.SinHalfAngle();
			float sy = y.SinHalfAngle();
			float sz = z.SinHalfAngle();

			float qw = (cx * cy * cz) + (sx * sy * sz);
			float qx = (sx * cy * cz) - (cx * sy * sz);
			float qy = (cx * sy * cz) + (sx * cy * sz);
			float qz = (cx * cy * sz) - (sx * sy * cz);

			return Quaternion(qx, qy, qz, qw);
		}

		static const Quaternion Identity;
	};
}
