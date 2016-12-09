#include "../pch.h"
#include "Transform.h"
#include "../GL/GLDevice.h"

namespace Model
{
	using namespace Math3d;

	Transform::Transform()
	{
		m_scale = Vector3f(1.0f);
	}

	Transform::~Transform() { }

	void Transform::SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	Quaternion Transform::GetRotation() const
	{
		return m_rotation;
	}

	void Transform::Update()
	{
		Matrix scale = MakeScale(m_scale);
		Matrix rotation = MakeRotation(m_rotation);
		Matrix translation = MakeTranslate(m_position);
		
		m_model.Identity();
		m_model = translation * rotation * scale;
	}

	Transform& Transform::Translate(const Vector3f& position)
	{
		m_position += position;
		return *this;
	}

	Transform& Transform::Translate(float x, const float y, const float z)
	{
		return Translate(Vector3f(x, y, z));
	}

	Transform& Transform::Scale(const Vector3f& scale)
	{
		m_scale += scale;
		return *this;
	}

	Transform& Transform::Scale(const float x, const float y, const float z)
	{
		return Scale(Vector3f(x, y, z));
	}

	Transform& Transform::Scale(const float s)
	{
		return Scale(Vector3f(s));
	}

	Transform& Transform::Rotate(const Quaternion& rotation)
	{
		m_rotation = rotation * m_rotation;

		return *this;
	}

	Transform& Transform::RotateX(float theta)
	{
		Angle t = Angle::FromDegrees(theta);
		Quaternion rotation = Quaternion::FromAxisAngle(t, Vector3f::UnitX);
		m_rotation = rotation * m_rotation;

		return *this;
	}

	Transform& Transform::RotateY(float theta)
	{
		Angle t = Angle::FromDegrees(theta);
		Quaternion rotation = Quaternion::FromAxisAngle(t, Vector3f::UnitY);
		m_rotation = rotation * m_rotation;

		return *this;
	}

	Transform&  Transform::RotateZ(float theta)
	{
		Angle t = Angle::FromDegrees(theta);
		Quaternion rotation = Quaternion::FromAxisAngle(t, Vector3f::UnitZ);
		m_rotation = rotation * m_rotation;

		return *this;
	}

	Matrix Transform::GetModelToClip() const
	{
		return m_model;
	}
}
