#include "VertexBufferObject.h"
#include "ObjFile.h"
#include "Semantic.h"

VertexBufferObject::VertexBufferObject(): m_vao(0), m_attributeBuffer(0), m_indexBuffer(0) { }

VertexBufferObject::~VertexBufferObject() { }

void VertexBufferObject::Load(const char* filename)
{
	ObjFile f = ObjFile(filename);

	std::vector<Vector3f> pos;
	std::vector<Vector2f> uvs;
	std::vector<Vector3f> normals;
	std::vector<GLuint> indices;

	f.GetMeshData(pos, uvs, normals, indices);

	int len = pos.size();
	m_info.numVertices = len * 3;
	m_info.numIndices = indices.size();
	m_info.size = len * 3 * sizeof(float);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glCreateBuffers(1, &m_attributeBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffer);
	glBufferStorage(GL_ARRAY_BUFFER, m_info.size, &pos[0], 0);

	glCreateBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_info.numIndices * sizeof(GLuint), &indices[0], 0);

	glVertexAttribPointer(Attrib::Position, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
	glEnableVertexAttribArray(Attrib::Position);

	/*glVertexAttribPointer(Attrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(&m_info.size));
	glEnableVertexAttribArray(Attrib::Normal);*/
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
