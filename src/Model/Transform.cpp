#include "../pch.h"
#include "Transform.h"

namespace Model
{
	Transform::Transform()
	{
		m_scale = Math3d::MakeScale(1.0f, 1.0f, 1.0f);
	}

	Transform::~Transform() { }

	void Transform::Update()
	{
		m_model *= m_trans * m_rot * m_scale;
		m_trans.Identity();
		m_rot.Identity();
		m_scale.Identity();
	}

	void Transform::Translate(const Math3d::Vector3f& vector)
	{
		m_trans *= MakeTranslate(vector);
	}

	Transform& Transform::Scale(const float s)
	{
		m_scale *= Math3d::MakeScale(Math3d::Vector3f(s));
		return *this;
	}

	Transform& Transform::Scale(const Math3d::Vector3f& vector)
	{
		m_scale *= MakeScale(vector);
		return *this;
	}

	Transform& Transform::RotateX(float theta)
	{
		m_rot *= Math3d::MakeRotationX(theta);
		return *this;
	}

	Transform& Transform::RotateY(float theta)
	{
		m_rot *= Math3d::MakeRotationY(theta);
		return *this;
	}

	Transform&  Transform::RotateZ(float theta)
	{
		m_rot *= Math3d::MakeRotationZ(theta);
		return *this;
	}

	Math3d::Matrix& Transform::GetModelToClip()
	{
		return m_model;
	}
}
