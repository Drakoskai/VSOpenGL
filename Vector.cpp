#include "Vector.h"
#include "math.h"
#include <sstream>
#include "Geometry.h"

#pragma region Vector2

const Vector2f Vector2f::Zero(0.f, 0.f);
const Vector2f Vector2f::One(1.0f, 1.0f);
const Vector2f Vector2f::UnitX(1.0f, 0.0f);
const Vector2f Vector2f::UnitY(0.0f, 1.0f);

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

float Vector2f::operator[](const int index) const
{
	return (&x)[index];
}

float& Vector2f::operator[](const int index)
{
	return (&x)[index];
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

const Vector3f Vector3f::Zero(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::One(1.0f, 1.0f, 1.0f);
const Vector3f Vector3f::UnitX(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::UnitY(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::Up(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::Down(0.0f, -1.0f, 0.0f);
const Vector3f Vector3f::Right(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::Left(-1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::Forward(0.0f, 0.0f, -1.0f);
const Vector3f Vector3f::Backward(0.0f, 0.0f, 1.0f);

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

float Vector3f::operator[](const int index) const
{
	return (&x)[index];
}

float& Vector3f::operator[](const int index)
{
	return (&x)[index];
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

float Vector3f::GetLength() const
{
	return sqrtf(GetLengthSqrd());
}

float Vector3f::GetLengthSqrd() const
{
	return  x * x + y * y + z * z;
}

float Vector3f::Normalize()
{
	float sqrLength = x * x + y * y + z * z;

	float invLength = Geometry::InvSqrt(sqrLength);
	x *= invLength;
	y *= invLength;
	z *= invLength;

	return invLength * sqrLength;
}

Vector3f Vector3f::NormalizeTo() const
{
	float length = GetLength();
	if (length == 0)
	{
		return Vector3f(x, y, z);
	}

	return Vector3f(x / length, y / length, z / length);
}

Vector3f Vector3f::Cross(Vector3f& other) const
{
	return Vector3f(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vector3f::Dot(const Vector3f& other) const
{
	return x * other.x + y * other.y + z * other.z;
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
Vector4f::Vector4f(float s) : x(s), y(s), z(s), w(s) { }
Vector4f::Vector4f(const Vector3f& v, const float s) : x(v.x), y(v.y), z(v.z), w(s) { }
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

float Vector4f::operator[](const int index) const
{
	return (&x)[index];
}

float& Vector4f::operator[](const int index)
{
	return (&x)[index];
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

float Vector4f::Dot(const Vector4f& v) const
{
	return x*v.x + y*v.y + z*v.z + w + v.w;
}

float Vector4f::Length() const
{
	return std::sqrt(Dot(*this));
}

Vector4f Vector4f::Normalize() const
{
	return *this / Length();
}

#pragma endregion Vector4

Color::Color()
{
	r = 0.0f;
	b = 0.0f;
	g = 0.0f;
	a = 1.0f;
}

Color::Color(float r_, float g_, float b_)
	: r(r_), g(g_), b(b_), a(1.0f) { }

Color::Color(float r_, float g_, float b_, float a_)
	: r(r_), g(g_), b(b_), a(a_) { }

Color::Color(const float* pArray)
	: r(pArray[0]), g(pArray[1]), b(pArray[2]), a(pArray[3]) { }

float Color::operator[](const int index) const
{
	return (&r)[index];
}

float& Color::operator[](const int index)
{
	return (&r)[index];
}
