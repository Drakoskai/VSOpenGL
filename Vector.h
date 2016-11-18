#pragma once

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3();
	explicit Vector3(float f);
	Vector3(float x, float y);
	Vector3(float x, float y, float z);
	explicit Vector3(const float *pArray);
	Vector3(const Vector3& other);

	bool operator ==(const Vector3& v)const;
	bool operator !=(const Vector3& v)const;
	Vector3& operator= (const Vector3& other);
	Vector3& operator+= (const Vector3& other);
	Vector3& operator-= (const Vector3& other);
	Vector3& operator*= (float s);
	Vector3& operator/= (float s);

	Vector3 operator-() const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const float s) const;
	Vector3 operator/(const float s) const;

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Forward;
	static const Vector3 Backward;

};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4();
	explicit Vector4(float f);
	Vector4(float x, float y);
	Vector4(float x, float y, float z);
	Vector4(float x, float y, float z, float w);
	explicit Vector4(const float *pArray);
	explicit Vector4(const Vector3& other);
	Vector4(const Vector4& other);

	bool operator ==(const Vector4& v)const;
	bool operator !=(const Vector4& v)const;
	Vector4& operator= (const Vector4& other);
	Vector4& operator+= (const Vector4& other);
	Vector4& operator-= (const Vector4& other);
	Vector4& operator*= (float s);
	Vector4& operator/= (float s);

	Vector4 operator-() const;
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator*(const float s) const;
	Vector4 operator/(const float s) const;

	static const Vector4 Zero;
	static const Vector4 One;
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 UnitW;

};

struct Color
{
	float x;
	float y;
	float z;
	float a;
};