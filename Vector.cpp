#include "Vector.h"
#include <sstream>

#pragma region Vector2

Vector2f::Vector2f() : x(0.0f), y(0.0f) { }

Vector2f::Vector2f(float s) : x(s), y(s) { }

Vector2f::Vector2f(float x_, float y_) : x(x_), y(y_) { }

Vector2f::Vector2f(const float* arr) : x(arr[0]), y(arr[1]) { }

Vector2f::Vector2f(const Vector2f& other) : x(other.x), y(other.y) { }

bool Vector2f::operator==(const Vector2f& other) const
{
	return other.x == x && other.y == y;
}

bool Vector2f::operator!=(const Vector2f& other) const
{
	return !(other.x == x && other.y == y);
}

Vector2f& Vector2f::operator=(const Vector2f& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2f& Vector2f::operator*=(float s)
{
	x *= s;
	y *= s;

	return *this;
}

Vector2f& Vector2f::operator/=(float s)
{
	float inva = 1.0f / s;
	x *= inva;
	y *= inva;

	return *this;
}

Vector2f Vector2f::operator-() const
{
	return Vector2f(-x, -y);
}

Vector2f Vector2f::operator+(const Vector2f& other) const
{
	return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f& other) const
{
	return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator*(const float s) const
{
	return Vector2f(x * s, y * s);
}

Vector2f Vector2f::operator/(const float s) const
{
	float inva = 1.0f / s;

	return Vector2f(x * inva, y * inva);
}


std::string Vector2f::ToString() const
{
	std::stringstream ss;
	ss << "Vector2:"
		<< '{'
		<< "x:"
		<< x
		<< ','
		<< "y:"
		<< y
		<< '}';

	return ss.str();
}

#pragma endregion Vector2

#pragma region Vector3

const Vector3f Vector3f::Zero(0.f, 0.f, 0.f);
const Vector3f Vector3f::One(1.f, 1.f, 1.f);
const Vector3f Vector3f::UnitX(1.f, 0.f, 0.f);
const Vector3f Vector3f::UnitY(0.f, 1.f, 0.f);
const Vector3f Vector3f::UnitZ(0.f, 0.f, 1.f);
const Vector3f Vector3f::Up(0.f, 1.f, 0.f);
const Vector3f Vector3f::Down(0.f, -1.f, 0.f);
const Vector3f Vector3f::Right(1.f, 0.f, 0.f);
const Vector3f Vector3f::Left(-1.f, 0.f, 0.f);
const Vector3f Vector3f::Forward(0.f, 0.f, -1.f);
const Vector3f Vector3f::Backward(0.f, 0.f, 1.f);

Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f) { }
Vector3f::Vector3f(float x_) : x(x_), y(x_), z(x_) { }
Vector3f::Vector3f(float x_, float y_) : x(x_), y(y_), z(0.0f) { }
Vector3f::Vector3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) { }
Vector3f::Vector3f(const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) { }
Vector3f::Vector3f(const Vector3f& other) : x(other.x), y(other.y), z(other.z) { }

bool Vector3f::operator==(const Vector3f& other) const
{
	return other.x == x && other.y == y && other.z == z;
}

bool Vector3f::operator!=(const Vector3f& other) const
{
	return !(other.x == x && other.y == y && other.z == z);
}

Vector3f& Vector3f::operator=(const Vector3f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3f& Vector3f::operator+=(const Vector3f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3f& Vector3f::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

Vector3f& Vector3f::operator/=(float s)
{
	float inva = 1.0f / s;
	x *= inva;
	y *= inva;
	z *= inva;

	return *this;
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator+(const Vector3f& other) const
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator-(const Vector3f& other) const
{
	return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator*(const float s) const
{
	return Vector3f(x * s, y * s, z * s);
}

Vector3f Vector3f::operator/(const float s) const
{
	float inva = 1.0f / s;
	return Vector3f(x * inva, y * inva, z * inva);
}

std::string Vector3f::ToString() const
{
	std::stringstream ss;
	ss << "Vector3:"
		<< '{'
		<< "x:"
		<< x
		<< ','
		<< "y:"
		<< y
		<< ','
		<< "z:"
		<< z
		<< '}';

	return ss.str();
}

#pragma endregion Vector3

#pragma region Vector4

const Vector4f Vector4f::Zero(0.0f);
const Vector4f Vector4f::One(1.0f);
const Vector4f Vector4f::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4f Vector4f::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4f Vector4f::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4f Vector4f::UnitW(0.0f, 0.0f, 0.0f, 1.0f);

Vector4f::Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
Vector4f::Vector4f(float f) : x(f), y(f), z(f), w(f) { }
Vector4f::Vector4f(float x_, float y_) : x(x_), y(y_), z(0.0f), w(0.0f) { }
Vector4f::Vector4f(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(0.0f) { }
Vector4f::Vector4f(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) { }
Vector4f::Vector4f(const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) { }
Vector4f::Vector4f(const Vector3f& other) : x(other.x), y(other.y), z(other.z), w(0.0f) { }
Vector4f::Vector4f(const Vector4f& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

bool Vector4f::operator==(const Vector4f& other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4f::operator!=(const Vector4f& other) const
{
	return !(x == other.x && y == other.y && z == other.z && w == other.w);
}

Vector4f& Vector4f::operator=(const Vector4f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Vector4f& Vector4f::operator+=(const Vector4f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4f& Vector4f::operator-=(const Vector4f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Vector4f& Vector4f::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;

	return *this;
}

Vector4f& Vector4f::operator/=(float s)
{
	float inva = 1.0f / s;
	x *= inva;
	y *= inva;
	z *= inva;
	w *= inva;

	return *this;
}

Vector4f Vector4f::operator-() const
{
	return Vector4f(-x, -y, -z, -w);
}

Vector4f Vector4f::operator+(const Vector4f& other) const
{
	return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4f Vector4f::operator-(const Vector4f& other) const
{
	return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4f Vector4f::operator*(const float s) const
{
	return Vector4f(x * s, y * s, z * s, w * s);
}

Vector4f Vector4f::operator/(const float s) const
{
	float inva = 1.0f / s;
	return Vector4f(x * inva, y * inva, z * inva, w * inva);
}

#pragma endregion Vector4
