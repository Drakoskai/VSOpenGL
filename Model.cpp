#include "Model.h"
#include <vector>
#include "ObjFile.h"
#include <iostream>
#include <GL/glew.h>
#include "GLSemantic.h"


Model::Model(const std::string& filename)
	: m_filename(filename), m_vaoId(0), m_vboid(0), m_idxid(0), m_transformid(0),
	m_shaderProgram(0), m_transformPointer(nullptr) { }

Model::~Model() { }

void Model::Init(GLDrawContext* dc)
{
	ObjFile file = ObjFile(m_filename);
	file.GetMeshData(m_vertexData, m_uvData, m_normalData, m_idxData);

	GLuint vertShaderId = dc->LoadShader("basic.vert");
	GLuint fragShaderId = dc->LoadShader("basic.frag");

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertShaderId);
	glAttachShader(m_shaderProgram, fragShaderId);
	glLinkProgram(m_shaderProgram);

	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
	glCreateBuffers(4, &m_vboid);

	glBufferStorage(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Vector3f), &m_vertexData[0], 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idxid);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_idxData.size() * sizeof(unsigned short), &m_idxData[0], 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, m_transformid);
	GLint * uniformBufferOffset = new GLint[1];
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, uniformBufferOffset);
	int uniformBlockSize = max(16 * sizeof(float), uniformBufferOffset[0]);
	glBufferStorage(GL_UNIFORM_BUFFER, uniformBlockSize, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	delete[] uniformBufferOffset;
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glVertexArrayElementBuffer(dc->GetVaoId(), m_idxid);
	glVertexArrayVertexBuffer(dc->GetVaoId(), Semantic::Stream::_0, m_vboid, 0, m_vertexData.size() * sizeof(Vector3f));
	m_transformPointer = reinterpret_cast<float*>(glMapNamedBufferRange(m_transformid,
		0,
		16 * sizeof(float),
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
}

Transform Model::GetTransform() { return m_transform; }

void Model::Update(float dt) { }

void Model::Draw()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, Semantic::Uniform::Transform0, m_vboid);
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vaoId);
	glDrawElements(GL_TRIANGLES, m_idxData.size(), GL_UNSIGNED_SHORT, &m_idxData[0]);
}

void Model::Release()
{
	glUnmapNamedBuffer(m_transformid);
	glDeleteBuffers(1, &m_idxid);
	glDeleteBuffers(1, &m_vboid);
	glDeleteProgram(m_shaderProgram);
	glDeleteVertexArrays(1, &m_vaoId);
}
