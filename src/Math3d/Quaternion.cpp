#include "../pch.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Geometry.h"

namespace Math3d
{
	const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	const Quaternion Quaternion::Zero = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) { }

	Quaternion::Quaternion(float x_, float y_, float z_, float w_)
		: x(x_), y(y_), z(z_), w(w_) { }

	bool Quaternion::operator==(const Quaternion& other) const { return x == other.x && y == other.y && z == other.z && w == other.w ? true : false; }
	
	bool Quaternion::operator!=(const Quaternion& other) const { return x == other.x && y == other.y && z == other.z && w == other.w ? false : true; }

	Quaternion Quaternion::operator+(const Quaternion& other) const	{ return Quaternion{ x + other.x, y + other.y, z + other.z, w + other.w }; }

	Quaternion Quaternion::operator-(const Quaternion& other) const	{ return Quaternion{ x - other.x, y - other.y, z - other.z, w - other.w }; }

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

	Quaternion::operator float*() { return static_cast<float*>(&x);	}

	Quaternion::operator const float*() const { return static_cast<const float*>(&x); }

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

	Vector3f Quaternion::GetAxis() const
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

		return Vector3f{ x_, y_, z_ };
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
		float radians = asinf((2.0f * x * y) + (2.0f * z * w));

		return Angle::FromRadians(radians);
	}

	Vector3f Quaternion::GetUp() const
	{
		return Vector3f{ 2.0f * (x * y - w * z),
			1.0f - 2.0f * (x * x + z * z),
			2.0f * (y * z + w * x) };
	}

	Vector3f Quaternion::GetRight() const
	{
		return Vector3f{ 1.0f - 2.0f * (y * y + z * z),
			2.0f * (x * y + w * z),
			2.0f * (x * z - w * y) };
	}

	Vector3f Quaternion::GetForward() const
	{
		return Vector3f{ 2.0f * (x * z + w * y),
			2.0f * (y * x - w * x),
			1.0f - 2.0f * (x * x + y * y) };
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

	Quaternion Quaternion::FromMatrix(const Matrix& m)
	{
		float t = 1.0f + m.mat[0][0] + m.mat[1][1] + m.mat[2][2];
		float x;
		float y;
		float z;
		float w;
		float s;
		const float Epsilon = 0.00000001f;
		if (t > Epsilon)
		{
			s = 2.0f * sqrtf(t);
			x = (m.mat[2][1] - m.mat[1][2]) / s;
			y = (m.mat[0][2] - m.mat[2][0]) / s;
			z = (m.mat[1][0] - m.mat[0][1]) / s;
			w = s / 4.0f;
		}
		else if (m.mat[0][0] > m.mat[1][1] && m.mat[0][0] > m.mat[2][2])
		{
			s = 2.0f * sqrtf(1.0f + m.mat[0][0] - m.mat[1][1] - m.mat[2][2]);
			x = s / 4.0f;
			y = (m.mat[1][0] + m.mat[0][1]) / s;
			z = (m.mat[0][2] + m.mat[2][0]) / s;
			w = (m.mat[2][1] - m.mat[1][2]) / s;
		}
		else if (m.mat[1][1] > m.mat[2][2])
		{
			s = 2.0f * sqrtf(1.0f + m.mat[1][1] - m.mat[0][0] - m.mat[2][2]);
			x = (m.mat[1][0] + m.mat[0][1]) / s;
			y = s / 4.0f;
			z = (m.mat[2][1] + m.mat[1][2]) / s;
			w = (m.mat[0][2] - m.mat[2][0]) / s;
		}
		else
		{
			s = 2.0f * sqrtf(1.0f + m.mat[2][2] - m.mat[0][0] - m.mat[1][1]);
			x = (m.mat[0][2] + m.mat[2][0]) / s;
			y = (m.mat[2][1] + m.mat[1][2]) / s;
			z = s / 4.0f;
			w = (m.mat[1][0] - m.mat[0][1]) / s;
		}

		return Quaternion{ x, y, z, w };
	}

	Quaternion Quaternion::MakeLookAt(Vector4f sourcePoint, Vector4f destPoint)
	{
		const float Epsilion = 0.000001f;
		Vector4f forwardVector = Normalize(destPoint - sourcePoint);

		float dot = Dot(Vector4f::Forward, forwardVector);

		if (abs(dot - (-1.0f)) < Epsilion)
		{
			return Quaternion(Vector4f::Up.x, Vector4f::Up.y, Vector4f::Up.z, Geometry::PI);
		}
		if (abs(dot - (1.0f)) < Epsilion)
		{
			return Identity;
		}

		float rotAngle = acosf(dot);
		Vector4f rotAxis = Cross(Vector4f::Forward, forwardVector);
		rotAxis = Normalize(rotAxis);

		return FromAxisAngle(Angle::FromDegrees(rotAngle), rotAxis);
	}

	Quaternion Cross(const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion{
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x};
	}

	Quaternion Normalize(const Quaternion& q)
	{
		float length = q.Length();
		if (length != 0.0f && length != -0.0f)
		{
			float ilength;
			ilength = 1 / length;
			return Quaternion{q.x / ilength, q.y / ilength, q.z / ilength, q.w / ilength};
		}

		return Quaternion{q.x, q.y, q.z, q.w};
	}
}
