#include "Vector.h"

#pragma region Vector3

const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
const Vector3 Vector3::One(1.f, 1.f, 1.f);
const Vector3 Vector3::UnitX(1.f, 0.f, 0.f);
const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);
const Vector3 Vector3::Up(0.f, 1.f, 0.f);
const Vector3 Vector3::Down(0.f, -1.f, 0.f);
const Vector3 Vector3::Right(1.f, 0.f, 0.f);
const Vector3 Vector3::Left(-1.f, 0.f, 0.f);
const Vector3 Vector3::Forward(0.f, 0.f, -1.f);
const Vector3 Vector3::Backward(0.f, 0.f, 1.f);

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
Vector3::Vector3(float x_) : x(x_), y(x_), z(x_) { }
Vector3::Vector3(float x_, float y_) : x(x_), y(y_), z(0.0f) { }
Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) { }
Vector3::Vector3(const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) { }
Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) { }

bool Vector3::operator==(const Vector3& other) const
{
	return other.x == x && other.y == y && other.z == z;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(other.x == x && other.y == y && other.z == z);
}

Vector3& Vector3::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	float inva = 1.0f / s;
	x *= inva;
	y *= inva;
	z *= inva;

	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const float s) const
{
	return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(const float s) const
{
	float inva = 1.0f / s;
	return Vector3(x * inva, y * inva, z * inva);
}

#pragma endregion Vector3

#pragma region Vector4

const Vector4 Vector4::Zero(0.0f);
const Vector4 Vector4::One(1.0f);
const Vector4 Vector4::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UnitW(0.0f, 0.0f, 0.0f, 1.0f);

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
Vector4::Vector4(float f) : x(f), y(f), z(f), w(f) { }
Vector4::Vector4(float x_, float y_) : x(x_), y(y_), z(0.0f), w(0.0f) { }
Vector4::Vector4(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(0.0f) { }
Vector4::Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) { }
Vector4::Vector4(const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) { }
Vector4::Vector4(const Vector3& other) : x(other.x), y(other.y), z(other.z), w(0.0f) { }
Vector4::Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

bool Vector4::operator==(const Vector4& other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(const Vector4& other) const
{
	return !(x == other.x && y == other.y && z == other.z && w == other.w);
}

Vector4& Vector4::operator=(const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Vector4& Vector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;

	return *this;
}

Vector4& Vector4::operator/=(float s)
{
	float inva = 1.0f / s;
	x *= inva;
	y *= inva;
	z *= inva;
	w *= inva;

	return *this;
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator*(const float s) const
{
	return Vector4(x * s, y * s, z * s, w * s);
}

Vector4 Vector4::operator/(const float s) const
{
	float inva = 1.0f / s;
	return Vector4(x * inva, y * inva, z * inva, w * inva);
}

#pragma endregion Vector4
