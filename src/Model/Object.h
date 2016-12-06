#pragma once

#include "Transform.h"
#include "../GL/VertexBufferObject.h"
#include "../Math3d/Matrix.h"
#include "../GL/ShaderUtil.h"

namespace Model
{
	class Object
	{
	public:
		Object(const char* filename);
		~Object();

		Transform& GetTransform();
		void Update(const Math3d::Matrix& proj);
		void Draw() const;

	private:
		bool Init();
		Transform m_transform;
		Math3d::Matrix m_mvp;

		OpenGL::VertexBufferObject m_object;
		OpenGL::Shader* m_shader;	
	};
}
