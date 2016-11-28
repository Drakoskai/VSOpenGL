#pragma once

#include <string>


#pragma region Vector2f

struct Vector2f
{
	float x;
	float y;

	Vector2f();
	explicit Vector2f(float f);
	Vector2f(float x, float y);
	explicit Vector2f(const float *pArray);
	Vector2f(const Vector2f& other);

	bool operator ==(const Vector2f& v)const;
	bool operator !=(const Vector2f& v)const;

	float operator[](const int index) const;
	float& operator[](const int index);

	Vector2f& operator= (const Vector2f& other);
	Vector2f& operator+= (const Vector2f& other);
	Vector2f& operator-= (const Vector2f& other);
	Vector2f& operator*= (float s);
	Vector2f& operator/= (float s);

	Vector2f operator-() const;
	Vector2f operator+(const Vector2f& other) const;
	Vector2f operator-(const Vector2f& other) const;
	Vector2f operator*(const float s) const;
	Vector2f operator/(const float s) const;

	std::string ToString() const;

};

#pragma endregion Vector2f

#pragma region Vector3f

struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f();
	explicit Vector3f(float f);
	Vector3f(float x, float y);
	Vector3f(float x, float y, float z);
	explicit Vector3f(const float *pArray);
	Vector3f(const Vector3f& other);

	bool operator ==(const Vector3f& v)const;
	bool operator !=(const Vector3f& v)const;
	Vector3f& operator= (const Vector3f& other);
	Vector3f& operator+= (const Vector3f& other);
	Vector3f& operator-= (const Vector3f& other);
	Vector3f& operator*= (float s);
	Vector3f& operator/= (float s);

	Vector3f operator-() const;
	float operator[](const int index) const;
	float& operator[](const int index);
	Vector3f operator+(const Vector3f& other) const;
	Vector3f operator-(const Vector3f& other) const;
	Vector3f operator*(const float s) const;
	Vector3f operator/(const float s) const;

	float GetLength() const;
	float GetLengthSqrd() const;

	float Normalize();
	Vector3f NormalizeTo() const;
	Vector3f Cross(Vector3f& other) const;
	float Dot(const Vector3f& other) const;

	std::string ToString() const;

	static const Vector3f Zero;
	static const Vector3f One;
	static const Vector3f UnitX;
	static const Vector3f UnitY;
	static const Vector3f UnitZ;
	static const Vector3f Up;
	static const Vector3f Down;
	static const Vector3f Left;
	static const Vector3f Right;
	static const Vector3f Forward;
	static const Vector3f Backward;

};

#pragma endregion Vector3f

#pragma region Vector4f

struct Vector4f
{
	float x;
	float y;
	float z;
	float w;

	Vector4f();
	explicit Vector4f(float f);
	Vector4f(float x, float y);
	Vector4f(float x, float y, float z);
	Vector4f(float x, float y, float z, float w);
	explicit Vector4f(const float *pArray);
	explicit Vector4f(const Vector3f& other);
	Vector4f(const Vector4f& other);

	bool operator ==(const Vector4f& v)const;
	bool operator !=(const Vector4f& v)const;
	Vector4f& operator= (const Vector4f& other);
	Vector4f& operator+= (const Vector4f& other);
	Vector4f& operator-= (const Vector4f& other);
	Vector4f& operator*= (float s);
	Vector4f& operator/= (float s);

	Vector4f operator-() const;
	float operator[](const int index) const;
	float& operator[](const int index);

	Vector4f operator+(const Vector4f& other) const;
	Vector4f operator-(const Vector4f& other) const;
	Vector4f operator*(const float s) const;
	Vector4f operator/(const float s) const;

	static const Vector4f Zero;
	static const Vector4f One;
	static const Vector4f UnitX;
	static const Vector4f UnitY;
	static const Vector4f UnitZ;
	static const Vector4f UnitW;

};

#pragma endregion Vector4f

#pragma region Color

struct Color
{
	float r;
	float g;
	float b;
	float a;
	
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	explicit Color(const float *pArray);

	float operator[](const int index) const;
	float& operator[](const int index);
};

#pragma endregion Color