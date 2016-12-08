#pragma once

#include "../Math3d/Matrix.h"

namespace Model
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void Update();
		void Translate(const Math3d::Vector3f& vector);
		Transform& Scale(const float s);
		Transform& Scale(const Math3d::Vector3f& vec);
		Transform& RotateX(float theta);
		Transform& RotateY(float theta);
		Transform& RotateZ(float theta);
		Math3d::Matrix& GetModelToClip();

	private:
		Math3d::Matrix m_scale;
		Math3d::Matrix m_trans;
		Math3d::Matrix m_rot;
		Math3d::Matrix m_model;
	};
}
