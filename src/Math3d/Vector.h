#pragma once

#include <string>

namespace Math3d
{
	struct Matrix;

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

		operator const float*() const;
		operator float*();

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
		friend std::ostream& operator<<(std::ostream& os, const Vector2f& v);
		friend std::istream& operator>>(std::istream& is, Vector2f& v);

		static const Vector2f Zero;
		static const Vector2f One;
		static const Vector2f UnitX;
		static const Vector2f UnitY;
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

		operator const float*() const;
		operator float*();

		Vector3f operator+(const Vector3f& other) const;
		Vector3f operator-(const Vector3f& other) const;
		Vector3f operator*(const float s) const;
		Vector3f operator/(const float s) const;

		std::string ToString() const;
		friend std::ostream& operator<<(std::ostream& os, const Vector3f& v);
		friend std::istream& operator>>(std::istream& is, Vector3f& v);

		float GetLength() const;
		float GetLengthSqrd() const;

		float Normalize();
		Vector3f Cross(Vector3f& other) const;
		float Dot(const Vector3f& other) const;

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
		Vector4f(const Vector3f& v, const float s = 1.0);
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
		Vector4f operator*(const Vector4f& other) const;
		Vector4f operator/(const float s) const;

		friend std::ostream& operator<<(std::ostream& os, const Vector4f& v);
		friend std::istream& operator>>(std::istream& is, Vector4f& v);

		operator const float*() const;
		operator float*();

		float Dot(const Vector4f& v) const;
		float Length() const;
		Vector4f Normalize() const;
		Vector4f Transform(const Matrix& matrix) const;

		static const Vector4f Zero;
		static const Vector4f One;
		static const Vector4f UnitX;
		static const Vector4f UnitY;
		static const Vector4f UnitZ;
		static const Vector4f UnitW;
		static const Vector4f Up;
		static const Vector4f Down;
		static const Vector4f Left;
		static const Vector4f Right;
		static const Vector4f Forward;
		static const Vector4f Backward;

	};

	float Dot(const Vector4f& u, const Vector4f& v);
	float Length(const Vector4f& v);
	Vector4f Normalize(const Vector4f& v);
	Vector4f Cross(const Vector4f& a, const Vector4f& b);

#pragma endregion Vector4f

#pragma region Color

	struct Color
	{
		float r;
		float g;
		float b;
		float a;

		Color()
		{
			r = 0.0f;
			b = 0.0f;
			g = 0.0f;
			a = 1.0f;
		}

		Color(float r_, float g_, float b_)
			: r(r_), g(g_), b(b_), a(1.0f) { }

		Color(float r_, float g_, float b_, float a_)
			: r(r_), g(g_), b(b_), a(a_) { }

		Color(const float* pArray)
			: r(pArray[0]), g(pArray[1]), b(pArray[2]), a(pArray[3]) { }

		operator const float* () const
		{
			return static_cast<const GLfloat*>(&r);
		}

		operator float* ()
		{
			return static_cast<GLfloat*>(&r);
		}

		friend std::ostream& operator << (std::ostream& os, const Color& c) {
			return os << "( " << c.r << ", " << c.g << ", " << c.b << ", " << c.a << " )";
		}

		friend std::istream& operator >> (std::istream& is, Color& c)
		{
			return is >> c.r >> c.g >> c.b >> c.a;
		}

		float operator[](const int index) const;
		float& operator[](const int index);
	};

	namespace Colors
	{
		static const Color Black(0.0f, 0.0f, 0.0f, 0.0f);
	}

#pragma endregion Color
}
