#include "../pch.h"
#include "Transform.h"
#include "../GL/GLDevice.h"

namespace Model
{
	using namespace Math3d;

	Transform::Transform() : m_scale(Vector4f::One) { }

	Transform::~Transform() { }

	void Transform::Update()
	{
		Matrix scale = MakeScale(m_scale);
		Matrix rotation = MakeRotation(m_rotation);
		Matrix translation = MakeTranslate(m_position);
		m_model = scale * rotation * translation;
	}

	Transform& Transform::SetPosition(const Vector4f& position)
	{
		m_position = position;
		return *this;
	}

	Transform& Transform::SetPosition(const Vector3f& position)
	{
		m_position = position;
		return *this;
	}

	Transform& Transform::SetPosition(float x, const float y, const float z)
	{
		return SetPosition(Vector3f(x, y, z));
	}

	Transform& Transform::Translate(const Vector4f& position)
	{
		m_position += position;
		return *this;
	}

	Transform& Transform::Translate(const Vector3f& position)
	{
		m_position += position;
		return *this;
	}

	Transform& Transform::Translate(float x, const float y, const float z) { return Translate(Vector3f(x, y, z)); }

	Transform& Transform::Scale(const Vector3f& scale)
	{
		m_scale += scale;
		return *this;
	}

	Transform& Transform::Scale(const float x, const float y, const float z) { return Scale(Vector3f(x, y, z)); }

	Transform& Transform::Scale(const float s) { return Scale(Vector3f(s)); }

	Transform& Transform::SetScale(const Vector3f& scale)
	{
		m_scale = scale;
		return *this;
	}

	Transform& Transform::SetScale(const float x, const float y, const float z)	{ return SetScale(Vector3f(x, y, z)); }

	Transform& Transform::SetScale(const float s) { return SetScale(s, s, s); }

	Transform& Transform::SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
		return *this;
	}

	Transform& Transform::Rotate(const Quaternion& rotation)
	{
		m_rotation = rotation * m_rotation;
		return *this;
	}

	Transform& Transform::RotateX(const Angle theta)
	{
		Quaternion rotation = Quaternion::FromAxisAngle(theta, Vector3f::UnitX);
		m_rotation = rotation * m_rotation;
		
		return *this;
	}

	Transform& Transform::RotateY(const Angle theta)
	{
		Quaternion rotation = Quaternion::FromAxisAngle(theta, Vector3f::UnitY);
		m_rotation = rotation * m_rotation;
		
		return *this;
	}

	Transform& Transform::RotateZ(const Angle theta)
	{
		Quaternion rotation = Quaternion::FromAxisAngle(theta, Vector3f::UnitZ);
		m_rotation = rotation * m_rotation;

		return *this;
	}

	Transform& Transform::RotateX(float theta) { return RotateX(Angle::FromDegrees(theta)); }

	Transform& Transform::RotateY(float theta) { return RotateY(Angle::FromDegrees(theta)); }

	Transform& Transform::RotateZ(float theta) { return RotateZ(Angle::FromDegrees(theta)); }

	Matrix Transform::GetModelToClip() const { return m_model; }

	Vector4f Transform::GetPosition() const { return m_position; }

	Quaternion Transform::GetRotation() const { return m_rotation; }

	Math3d::Vector4f Transform::GetForward() const { return m_rotation.GetForward(); }

	Vector4f Transform::GetRight() const { return m_rotation.GetRight(); }

}
