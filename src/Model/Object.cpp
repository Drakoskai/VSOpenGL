#include "../pch.h"
#include "Object.h"
#include "../Util/ObjFile.h"
#include "../Util/Util.h"

namespace Model
{
	using namespace OpenGL;
	using namespace Math3d;
	using namespace Util;

	Object::Object(const char* filename)
	{
		ObjFile f = ObjFile(filename);
		m_object.Load(filename);
		assert(Init());
	}

	Object::~Object()
	{
		SafeDelete(m_shader);
	}

	bool Object::Init()
	{
		std::vector<ShaderInfo> shaders = {
			{ GL_VERTEX_SHADER, "Assets/Shaders/default.vert" },
			{ GL_FRAGMENT_SHADER, "Assets/Shaders/default.frag" },
			{ GL_NONE, nullptr }
		};

		m_shader = new Shader(shaders);

		m_shader->Set();
		m_shader->m_uniformMVP = glGetUniformLocation(m_shader->m_shaderProg, "mvp");	
		m_shader->Unset();

		return true;
	}

	Transform& Object::GetTransform() { return m_transform; }

	void Object::Update(const Matrix& viewProj)
	{
		m_transform.Update();

		m_mvp = m_transform.GetModelToClip() * viewProj;
	}

	void Object::Draw() const
	{
		m_shader->Set();
		glUniformMatrix4fv(m_shader->m_uniformMVP, 1, GL_FALSE, m_mvp);
		m_object.Render();
		m_shader->Unset();
	}
}
