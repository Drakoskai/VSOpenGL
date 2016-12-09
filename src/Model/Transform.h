#pragma once

#include "../Math3d/Matrix.h"
#include "../Math3d/Quaternion.h"

namespace Model
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void Update();

		void SetRotation(const Math3d::Quaternion& rotation);
		Math3d::Quaternion GetRotation() const;

		Transform& Translate(const Math3d::Vector3f& vector);
		Transform& Translate(float x, const float  y, const float z);
		Transform& Scale(const Math3d::Vector3f& vec);
		Transform& Scale(const float x, const float  y, const float z);
		Transform& Scale(const float s);
		Transform& SetScale(const Math3d::Vector3f& vec);
		Transform& SetScale(const float x, const float  y, const float z);
		Transform& SetScale(const float s);
		Transform& Rotate(const Math3d::Quaternion& rotation);
		Transform& RotateX(const float theta);
		Transform& RotateY(const float theta);
		Transform& RotateZ(const float theta);
		Math3d::Matrix GetModelToClip() const;

	private:
		Math3d::Vector3f m_position;
		Math3d::Quaternion m_rotation;
		Math3d::Vector3f m_scale;
		Math3d::Matrix m_model;
	};
}
