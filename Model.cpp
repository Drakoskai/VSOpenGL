#include "Model.h"
#include "ShaderUtil.h"
#include "ObjFile.h"

Model::Model(const char* filename): m_shaderProg(0), m_uniformMVP(0), m_uniformModelView(0)
{
	ObjFile f = ObjFile(filename);
	m_object.Load(filename);
}

Model::~Model() { }

void Model::Init()
{
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "default.vert" },
		{ GL_FRAGMENT_SHADER, "default.frag" },
		{ GL_NONE, nullptr }
	};
	m_shaderProg = Util::LoadShaders(shaders);
	glUseProgram(m_shaderProg);
	m_uniformMVP = glGetUniformLocation(m_shaderProg, "modelViewProject");

	glUseProgram(0);
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

void Model::Release()
{
	glUseProgram(0);
	glDeleteProgram(m_shaderProg);
	m_object.Release();
}
