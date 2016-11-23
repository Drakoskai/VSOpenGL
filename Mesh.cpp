#include "Mesh.h"
#include "GLSemantic.h"

Mesh::Mesh(std::vector<Vector3f>& vertices, std::vector<unsigned int>& elements, GLint elementType)
	: vboName(nullptr), m_shaderProgram(0), m_transformPointer(nullptr)
{
	unsigned int len = vertices.size();
	unsigned int vertexCount = len * 3;

	float* verts = new float[len];
	for (int i = 0, j = 0; i < len; i += 3 , j++)
	{
		verts[i] = vertices[j].x;
		verts[i + 1] = vertices[j].y;
		verts[i + 2] = vertices[j].z;
	}

	m_buffers = GLBuffers();
	m_buffers.SetVertexData(verts, vertexCount);

	unsigned int numElements = elements.size();
	unsigned int* elementData = &elements[0];
	m_buffers.SetElementData(elementType, elementData, numElements);
}

Mesh::~Mesh() { Release(); }

void Mesh::Init(const GLDrawContext& dc)
{
	using namespace Buffers;
	
	vboName = new unsigned[Max];
	float * vertexBuffer = m_buffers.GetFloatBuffer(Vertex);
	unsigned int* elementBuffer = m_buffers.GetIntBuffer(Element);
	
	glCreateBuffers(Max, vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName[Vertex]);
	glBufferStorage(GL_ARRAY_BUFFER, m_buffers.GetSize(Vertex), vertexBuffer, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboName[Element]);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, m_buffers.GetSize(Element), elementBuffer, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, vboName[GLBuffer::Transform]);
	GLint * uniformBufferOffset = new GLint[1];
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, uniformBufferOffset);
	int uniformBlockSize = max(16 * sizeof(float), uniformBufferOffset[0]);
	glBufferStorage(GL_UNIFORM_BUFFER, uniformBlockSize, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	delete[] uniformBufferOffset;
	delete[] vertexBuffer;
	delete[] elementBuffer;

	glVertexArrayElementBuffer(dc.GetVaoId(), vboName[Element]);
	glVertexArrayVertexBuffer(dc.GetVaoId(), Semantic::Stream::_0, vboName[Vertex], 0, m_buffers.GetStride(Vertex));

	m_transformPointer = reinterpret_cast<float*>(glMapNamedBufferRange(vboName[GLBuffer::Transform],
		0,
		16 * sizeof(float),
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
}

void Mesh::Update(Transform& transform) const
{
	memcpy(m_transformPointer, transform.GetModelToClipMatrix(), sizeof(float) * 16);
}

void Mesh::Draw(const GLDrawContext& dc)
{
	using namespace Buffers;
/*	glBindVertexArray(dc.GetVaoId());
	glBindBufferBase(GL_UNIFORM_BUFFER, Semantic::Uniform::Transform0, vboName[Buffers::Transform]);
	glUseProgram(m_shaderProgram);
	
	glDrawElements(GL_TRIANGLES, m_buffers.GetCount(Element), GL_UNSIGNED_INT, nullptr);*/
}

void Mesh::Release() const
{
	if (vboName)
	{
		using namespace Buffers;

		glUnmapNamedBuffer(vboName[Buffers::Transform]);
		glDeleteBuffers(Max, vboName);
		delete[] vboName;
	}
}

void Mesh::SetShader(GLuint shaderProgram)
{
	m_shaderProgram = shaderProgram;
}
