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
		
		Transform& SetPosition(const Math3d::Vector3f& position);
		Transform& SetPosition(float x, const float  y, const float z);
		Transform& Translate(const Math3d::Vector3f& position);
		Transform& Translate(float x, const float  y, const float z);

		Transform& SetScale(const Math3d::Vector3f& scale);
		Transform& SetScale(const float x, const float  y, const float z);
		Transform& SetScale(const float s);
		Transform& Scale(const Math3d::Vector3f& scale);
		Transform& Scale(const float x, const float  y, const float z);
		Transform& Scale(const float s);

		Transform& SetRotation(const Math3d::Quaternion& rotation);
		Transform& Rotate(const Math3d::Quaternion& rotation);
		Transform& RotateX(const Math3d::Angle theta);
		Transform& RotateY(const Math3d::Angle theta);
		Transform& RotateZ(const Math3d::Angle theta);
		Transform& RotateX(const float theta);
		Transform& RotateY(const float theta);
		Transform& RotateZ(const float theta);
		
		Math3d::Matrix GetModelToClip() const;
		Math3d::Vector4f GetPosition() const;
		Math3d::Quaternion GetRotation() const;

	private:
		Math3d::Vector4f m_position;
		Math3d::Quaternion m_rotation;
		Math3d::Vector4f m_scale;
		Math3d::Matrix m_model;
	};
}
