#pragma once

#include "Transform.h"
#include "../GL/VertexBufferObject.h"
#include "../Math3d/Matrix.h"
#include "../GL/Shader.h"

namespace Model
{
	class Object
	{
	public:
		Object(const char* filename);
		~Object();

		Transform& GetTransform();
		void Update(const Math3d::Matrix& model, const Math3d::Matrix& projection, const Math3d::Vector4f viewPos);
		void Draw() const;

	private:
		bool Init();
		Transform m_transform;
		Math3d::Matrix m_modelView;
		Math3d::Vector4f m_viewPos;
		Math3d::Matrix m_projection;

		OpenGL::VertexBufferObject m_object;
		OpenGL::Shader* m_shader;
	};
}
