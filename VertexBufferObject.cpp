#include "pch.h"
#include "VertexBufferObject.h"
#include "ObjFile.h"
#include "Util.h"

VertexBufferObject::VertexBufferObject()
	: m_vao(0), m_attributeBuffer(0), m_indexBuffer(0), m_attributes(nullptr) { }

VertexBufferObject::~VertexBufferObject()
{
	if (glIsBuffer(m_indexBuffer))
	{
		glDeleteBuffers(1, &m_indexBuffer);
		m_indexBuffer = 0;
	}

	if (glIsBuffer(m_attributeBuffer))
	{
		glDeleteBuffers(1, &m_attributeBuffer);
		m_attributeBuffer = 0;
	}

	if (glIsVertexArray(m_vao))
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}

	SafeDeleteArr(m_attributes);
}

void VertexBufferObject::Load(const char* filename)
{
	ObjFile f = ObjFile(filename);

	std::vector<GLuint> indices;
	std::vector<Vertex> verts;

	f.GetVertices(verts, indices);

	GatherInfo(verts, indices);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glCreateBuffers(1, &m_attributeBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffer);
	glBufferStorage(GL_ARRAY_BUFFER, m_info.size, &verts[0], 0);

	glCreateBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_info.numIndices, &indices[0], 0);

	uint64_t offset = 0;
	for (uint32_t i = 0; i < m_info.numAttribs; i++)
	{
		CreateAttribute(i, BfrStorage(offset));
		offset += m_attributes[i].offset;
	}

	glBindVertexArray(0);
}

void VertexBufferObject::Render() const
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_info.numVertices);
	glBindVertexArray(0);
}

void VertexBufferObject::GatherInfo(const std::vector<Vertex>& verts, const std::vector<GLuint>& indices)
{
	uint32_t numVerts = verts.size();
	m_info.numVertices = numVerts;
	m_info.numIndices = indices.size() * sizeof(GLuint);
	m_info.size = numVerts * sizeof(Vertex);
	m_info.stride = sizeof(Vertex);
	
	m_info.numAttribs = 1;
	if (verts[0].normal != Vector3f::Zero)
	{
		m_info.numAttribs++;
	}

	m_attributes = new AttribInfo[m_info.numAttribs];
	
	m_attributes[0].size = 3;
	m_attributes[0].offset = sizeof(Vector3f);
	m_attributes[0].type = GL_FLOAT;
	m_attributes[0].normalized = GL_FALSE;

	if (m_info.numAttribs > 0)
	{
		m_attributes[1].size = 3;
		m_attributes[1].offset = sizeof(Vector3f);
		m_attributes[1].type = GL_FLOAT;
		m_attributes[1].normalized = GL_FALSE;
	}
}

void VertexBufferObject::CreateAttribute(const GLuint index, const GLvoid * pointer) const
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, m_attributes[index].size, m_attributes[index].type, m_attributes[index].normalized, m_info.stride, pointer);
}
