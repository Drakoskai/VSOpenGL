#include "VertexBufferObject.h"
#include "ObjFile.h"
#include "Semantic.h"

VertexBufferObject::VertexBufferObject(): m_vao(0), m_attributeBuffer(0), m_indexBuffer(0) { }

VertexBufferObject::~VertexBufferObject() { }

void VertexBufferObject::Load(const char* filename)
{
	ObjFile f = ObjFile(filename);

	std::vector<GLuint> indices;
	std::vector<Vertex> verts;
	f.GetMeshData(verts, indices);

	int len = verts.size();
	m_info.numVertices = len;
	m_info.numIndices = indices.size();
	m_info.size = len * sizeof(Vertex);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glCreateBuffers(1, &m_attributeBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffer);
	glBufferStorage(GL_ARRAY_BUFFER, m_info.size, &verts[0], 0);

	glCreateBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_info.numIndices * sizeof(GLuint), &indices[0], 0);

	glEnableVertexAttribArray(Attrib::Position);
	glEnableVertexAttribArray(Attrib::Normal);

	glVertexAttribPointer(Attrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(0));
	glVertexAttribPointer(Attrib::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((sizeof(float) * 3)));
}

void VertexBufferObject::Render() const
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_info.numVertices);
	glBindVertexArray(0);
}

void VertexBufferObject::Release()
{
	glDeleteBuffers(1, &m_indexBuffer);
	m_indexBuffer = 0;
	glDeleteBuffers(1, &m_attributeBuffer);
	m_attributeBuffer = 0;
	glDeleteVertexArrays(1, &m_vao);
	m_vao = 0;
}
