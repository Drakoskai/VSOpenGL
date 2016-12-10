#include "../pch.h"
#include "Quaternion.h"
namespace Math3d
{
	const Quaternion Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	const Quaternion Zero = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);;

	Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) { }

	Quaternion::Quaternion(float x_, float y_, float z_, float w_)
		: x(x_), y(y_), z(z_), w(w_) { }

	bool Quaternion::operator==(const Quaternion& other) const { return x == other.x && y == other.y && z == other.z && w == other.w ? true : false; }
	bool Quaternion::operator!=(const Quaternion& other) const { return x == other.x && y == other.y && z == other.z && w == other.w ? false : true; }

	Quaternion Quaternion::operator+(const Quaternion& other) const
	{
		return Quaternion{ x + other.x, y + other.y, z + other.z, w + other.w };
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const
	{
		return Quaternion{ x - other.x, y - other.y, z - other.z, w - other.w };
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		return Quaternion{
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y + y * other.w + z * other.x - x * other.z,
			w * other.z + z * other.w + x * other.y - y * other.x,
			w * other.w - x * other.x - y * other.y - z * other.z };
	}

	Quaternion Quaternion::operator*(const float s) const
	{
		return Quaternion{ x * s, y * s, z * s, w * s };
	}

	Quaternion Quaternion::operator/(const Quaternion& other) const
	{
		return Quaternion{ x / other.x, y / other.y, z / other.z, w / other.w };
	}

	Quaternion Quaternion::operator/(const float s) const
	{
		return Quaternion{ x / s, y / s, z / s, w / s };
	}

	Quaternion& Quaternion::operator*=(const Quaternion& other)
	{
		float x_ = w * other.x + x * other.w + y * other.z - z * other.y;
		float y_ = w * other.y + y * other.w + z * other.x - x * other.z;
		float z_ = w * other.z + z * other.w + x * other.y - y * other.x;
		float w_ = w * other.w - x * other.x - y * other.y - z * other.z;
		x = x_;
		y = y_;
		z = z_;
		w = w_;

		return *this;
	}

	Quaternion::operator float*()
	{
		return static_cast<float*>(&x);
	}

	Quaternion::operator const float*() const
	{
		return static_cast<const float*>(&x);
	}

	float Quaternion::Length() const
	{
		float len = x * x + y * y + z * z + w * w;
		return sqrtf(len);
	}

	std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
	{
		return os << "( " << quaternion.x << ", " << quaternion.y
			<< ", " << quaternion.z << ", " << quaternion.w << " )";
	}

	std::istream& operator>>(std::istream& is, Quaternion& quaternion)
	{
		return is >> quaternion.x >> quaternion.y >> quaternion.z >> quaternion.w;
	}

	Quaternion Quaternion::Normalize() const
	{
		float length = Length();
		if (length != 0.0f && length != -0.0f)
		{
			float ilength;
			ilength = 1 / length;
			return Quaternion(x / ilength, y / ilength, z / ilength, w / ilength);
		}

		return Quaternion(x, y, z, w);
	}

	Quaternion Quaternion::Inverse() const
	{
		float length = Length();
		if (length == 0.0f || length == -0.0f)
		{
			return Quaternion(*this);
		}

		return Quaternion{ (0.0f - x) / length, (0.0f - y) / length, (0.0f - z) / length, w / length };
	}

	Angle Quaternion::GetAngle() const
	{
		float w_ = w;
		float length = Length();
		if (length != 0.0f && length != -0.0f && length != 1.0f)
		{
			w_ /= length;
		}
		float radians = 2.0f * acosf(w_);

		return Angle::FromRadians(radians);
	}

	Vector4f Quaternion::GetAxis() const
	{
		float x_ = x;
		float y_ = y;
		float z_ = z;

		float length = Length();
		if (length != 0.0f && length != -0.0f && length != 1.0f)
		{
			x_ /= length;
			y_ /= length;
			z_ /= length;
		}

		float vecLength = sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
		if (vecLength != 0.0f && length != -0.0f && length != 1.0f)
		{
			x_ /= vecLength;
			y_ /= vecLength;
			z_ /= vecLength;
		}

		return Vector4f{ x_, y_, z_ };
	}

	Angle Quaternion::GetRotationX() const
	{
		float radians = atan2f((2.0f * x * w) - (2.0f * y * z), 1.0f - 2.0f * (x * x) - 2.0f * (z * z));

		return Angle::FromRadians(radians);
	}

	Angle Quaternion::GetRotationY() const
	{
		float radians = atan2f((2.0f * y * w) - (2.0f * x * z), 1.0f - (2.0f * y * y) - (2.0f * z * z));

		return Angle::FromRadians(radians);
	}

	Angle Quaternion::GetRotationZ() const
	{
		float radians = asinf((2.0 * x * y) + (2.0 * z * w));

		return Angle::FromRadians(radians);
	}

	Quaternion Quaternion::FromAxisAngle(const Angle& angle, const float x, const float y, const float z)
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

	Quaternion Quaternion::FromAxisAngle(const Angle& angle, const Vector4f& axis)
	{
		return FromAxisAngle(angle, axis.x, axis.y, axis.z);
	}

	Quaternion Quaternion::FromAxisAngle(const Angle& angle, const Vector3f& axis)
	{
		return FromAxisAngle(angle, axis.x, axis.y, axis.z);
	}

	Quaternion Quaternion::FromRotationEuler(const Angle& x, const Angle& y, const Angle& z)
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
}
