#include "../pch.h"
#include "VertexBufferObject.h"
#include "../Util/ObjFile.h"
#include "../Util/Util.h"

namespace OpenGL
{
	using namespace Util;
	using namespace Math3d;
	using namespace Model;

	VertexBufferObject::VertexBufferObject()
		: m_vao(0), m_attributeBuffer(0), m_indexBuffer(0), m_mode(0), m_attributes(nullptr) { }

	VertexBufferObject::~VertexBufferObject()
	{
		if (m_indexBuffer != 0)
		{
			glDeleteBuffers(1, &m_indexBuffer);
			m_indexBuffer = 0;
		}

		if (m_attributeBuffer != 0)
		{
			glDeleteBuffers(1, &m_attributeBuffer);
			m_attributeBuffer = 0;
		}

		if (m_vao != 0)
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

		Create(verts, indices);
	}

	void VertexBufferObject::SetAttributes(AttribInfo* attribs)
	{
		m_attributes = attribs;
	}

	void VertexBufferObject::Create(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glCreateBuffers(1, &m_attributeBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffer);
		glBufferStorage(GL_ARRAY_BUFFER, m_info.size, &vertices[0], 0);

		glCreateBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_info.numIndices, &indices[0], 0);

		uint64_t offset = 0;
		for (uint32_t i = 0; i < m_info.numAttribs; i++)
		{
			CreateAttribute(i, BfrStorage(offset));
			offset += m_attributes[i].offset;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexBufferObject::Render() const
	{
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, m_info.numVertices);
		glBindVertexArray(0);
	}

	void VertexBufferObject::GatherInfo(const std::vector<Vertex>& verts, const std::vector<uint32_t>& indices)
	{
		size_t numVerts = verts.size();
		m_info.numVertices = numVerts;
		m_info.numIndices = indices.size() * sizeof(uint32_t);
		m_info.size = numVerts * sizeof(Vertex);
		m_info.stride = sizeof(Vertex);

		m_info.numAttribs = 1;
		if (verts[0].normal != Vector3f::Zero)
		{
			m_info.numAttribs++;
		}

		AttribInfo* attribs = new AttribInfo[m_info.numAttribs];

		attribs[0].size = 3;
		attribs[0].offset = sizeof(Vector3f);
		attribs[0].type = GL_FLOAT;
		attribs[0].normalized = GL_FALSE;

		if (m_info.numAttribs > 0)
		{
			attribs[1].size = 3;
			attribs[1].offset = sizeof(Vector3f);
			attribs[1].type = GL_FLOAT;
			attribs[1].normalized = GL_FALSE;
		}
		SetAttributes(attribs);
	}

	void VertexBufferObject::CreateAttribute(const GLuint index, const GLvoid* pointer) const
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, m_attributes[index].size, m_attributes[index].type, m_attributes[index].normalized, m_info.stride, pointer);
	}
}
