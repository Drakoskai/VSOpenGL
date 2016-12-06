#include "pch.h"
#include "Model.h"
#include "ShaderUtil.h"
#include "ObjFile.h"

Model::Model(const char* filename): m_shaderProg(0), m_uniformMVP(0), m_uniformModelView(0)
{
	ObjFile f = ObjFile(filename);
	m_object.Load(filename);
	assert(Init());
}

Model::~Model()
{
	if (glIsShader(m_shaderProg))
	{
		glUseProgram(0);
		glDeleteProgram(m_shaderProg);
	}
}

bool Model::Init()
{
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "default.vert" },
		{ GL_FRAGMENT_SHADER, "default.frag" },
		{ GL_NONE, nullptr }
	};

	m_shaderProg = Util::LoadShaders(shaders);
	if (!glIsShader(m_shaderProg))
	{
		return false;
	}

	glUseProgram(m_shaderProg);
	m_uniformMVP = glGetUniformLocation(m_shaderProg, "modelViewProject");

	glUseProgram(0);

	return true;
}

Transform& Model::GetTransform() { return m_transform; }

void Model::Update(const Matrix& proj)
{
	m_transform.Update();
	Matrix mvp = m_transform.GetModelMatrix() * proj;
	glUseProgram(m_shaderProg);
	glUniformMatrix4fv(m_uniformMVP, 1, GL_FALSE, mvp);
	glUseProgram(0);
}

void Model::Draw() const
{
	glUseProgram(m_shaderProg);
	m_object.Render();
	glUseProgram(0);
}
