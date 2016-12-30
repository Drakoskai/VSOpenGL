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

	Object::~Object() { SafeDelete(m_shader); }

	bool Object::Init()
	{
		std::vector<ShaderInfo> shaders = {
			{ GL_VERTEX_SHADER, "Assets/Shaders/default_vs.glsl" },
			//{ GL_TESS_CONTROL_SHADER, "Assets/Shaders/default_tcs.glsl"},
			//{ GL_TESS_EVALUATION_SHADER, "Assets/Shaders/default_tes.glsl" },
			//{ GL_GEOMETRY_SHADER, "Assets/Shaders/explode_gs.glsl" },		
			{ GL_FRAGMENT_SHADER, "Assets/Shaders/phong_fs.glsl" },
			{ GL_NONE, nullptr }
		};

		m_shader = new Shader(shaders);
		m_shader->Set();

		m_shader->m_uniformProjection = glGetUniformLocation(m_shader->m_shaderProg, "projection");
		m_shader->m_uniformModel = glGetUniformLocation(m_shader->m_shaderProg, "modelView");
		m_shader->m_uniformViewPos = glGetUniformLocation(m_shader->m_shaderProg, "viewPos");
		
		m_shader->Unset();

		return true;
	}

	Transform& Object::GetTransform() { return m_transform; }

	void Object::Update(const Matrix& view, const Matrix& projection, const Vector4f viewPos)
	{
		m_transform.Update();
		m_modelView = m_transform.GetModelToClip() * view;
		m_viewPos = viewPos;
		m_projection = projection;
	}

	void Object::Draw() const
	{
		m_shader->Set();
		glUniformMatrix4fv(m_shader->m_uniformModel, 1, GL_FALSE, m_modelView);
		glUniformMatrix4fv(m_shader->m_uniformProjection, 1, GL_FALSE, m_projection);
		glUniformMatrix4fv(m_shader->m_uniformViewPos, 1, GL_FALSE, m_viewPos);
		m_object.Render();
		m_shader->Unset();
	}
}
