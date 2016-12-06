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

	void Transform::Translate(Math3d::Vector3f vector)
	{
		m_trans *= MakeTranslate(vector);
	}

	void Transform::Scale(Math3d::Vector3f vec)
	{
		m_scale *= MakeScale(vec);
	}

	void Transform::RotateX(float theta)
	{
		m_rot *= Math3d::MakeRotationX(theta);
	}

	void Transform::RotateY(float theta)
	{
		m_rot *= Math3d::MakeRotationY(theta);
	}

	void Transform::RotateZ(float theta)
	{
		m_rot *= Math3d::MakeRotationZ(theta);
	}

	Math3d::Matrix& Transform::GetModelMatrix()
	{
		return m_model;
	}
}
