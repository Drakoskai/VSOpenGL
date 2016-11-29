#include "Transform.h"

Transform::Transform()
{
	m_scale = MakeScale(1.0f, 1.0f, 1.0f);
}

Transform::~Transform() { }

void Transform::Update()
{
	m_modelview *= m_trans * m_rot * m_scale;
	m_trans.Identity();
	m_rot.Identity();
	m_scale.Identity();
}

void Transform::Translate(Vector3f vector)
{
	m_trans *= MakeTranslate(vector);
}

void Transform::Scale(Vector3f vec)
{
	m_scale *= MakeScale(vec);
}

void Transform::RotateX(float theta)
{
	m_rot *= MakeRotationX(theta);
}

void Transform::RotateY(float theta)
{
	m_rot *= MakeRotationY(theta);
}

void Transform::RotateZ(float theta)
{
	m_rot *= MakeRotationZ(theta);
}

Matrix& Transform::GetModelView()
{
	return m_modelview;
}
