#include "GLBuffers.h"
#include <GL/glew.h>
#include <gl/gl.h>
#include "GLAttrib.h"
#include "GLSemantic.h"

GLBuffers::GLBuffers()
	: m_vertexData(nullptr), m_normalData(nullptr), m_elementData(nullptr), p_transform(nullptr) { }

GLBuffers::~GLBuffers()
{
	if (m_vertexData)
	{
		delete m_vertexData;
		m_vertexData = nullptr;
	}
	if (m_normalData)
	{
		delete m_normalData;
		m_normalData = nullptr;
	}
	if (m_elementData)
	{
		delete m_elementData;
		m_elementData = nullptr;
	}
	if (p_transform)
	{
		delete p_transform;
		p_transform = nullptr;
	}
}

int GLBuffers::GetMode(Buffers::GLBuffer type)
{
	return m_mode[type];
}

void GLBuffers::SetMode(Buffers::GLBuffer type, int mode)
{
	m_mode[type] = mode;
}

int GLBuffers::GetCount(Buffers::GLBuffer type)
{
	return m_count[type];
}

unsigned int GLBuffers::GetSize(Buffers::GLBuffer type)
{
	return m_size[type];
}

int GLBuffers::GetGLType(Buffers::GLBuffer type)
{
	return m_glType[type];
}

unsigned int GLBuffers::GetId(Buffers::GLBuffer type)
{
	return m_vboId[type];
}

unsigned GLBuffers::GetStride(Buffers::GLBuffer type)
{
	return m_stride[type];
}

void GLBuffers::SetElementData(int mode, int* src, unsigned int numElements)
{
	m_elementData = src;
	m_mode[Buffers::Element] = mode;
	m_size[Buffers::Element] = 1;
	m_glType[Buffers::Element] = GL_UNSIGNED_INT;
	m_count[Buffers::Element] = numElements;
}

void GLBuffers::SetVertexData(float* src, unsigned int numVerts)
{
	m_vertexData = src;
	m_size[Buffers::Vertex] = numVerts * GLAttribs::PositionSize;
	m_glType[Buffers::Vertex] = GLAttribs::PositionType;
	m_stride[Buffers::Vertex] = 3 * sizeof(float);
	m_count[Buffers::Vertex] = numVerts;
}

void GLBuffers::SetNormalData(float* src, unsigned int numNormals)
{
	m_normalData = src;
	m_size[Buffers::Normal] = numNormals * GLAttribs::NormalSize;
	m_glType[Buffers::Normal] = GLAttribs::NormalType;
	m_count[Buffers::Normal] = numNormals;
	m_stride[Buffers::Normal] = 3 * sizeof(float);
}

void GLBuffers::InitBuffers(GLDrawContext * dc)
{
	GLuint vboId;
	glGenBuffers(Buffers::Name, &vboId);
	m_vboId[Buffers::Vertex] = vboId;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId[Buffers::Vertex]);
	glBufferData(GL_ARRAY_BUFFER,
		GetSize(Buffers::Vertex),
		m_vertexData,
		GetMode(Buffers::Vertex));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboId[Buffers::Element]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		GetSize(Buffers::Element),
		m_elementData,
		GetMode(Buffers::Element));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, m_vboId[Buffers::Transform]);
	GLint * uniformBufferOffset = new GLint[1];
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, uniformBufferOffset);
	int uniformBlockSize = max(16 * sizeof(float), uniformBufferOffset[0]);
	glBufferStorage(GL_UNIFORM_BUFFER, uniformBlockSize, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	delete[] uniformBufferOffset;
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glVertexArrayElementBuffer(dc->GetVaoId(), m_vboId[Buffers::Element]);
	glVertexArrayVertexBuffer(dc->GetVaoId(), Semantic::Stream::_0, m_vboId[Buffers::Vertex], 0, GetStride(Buffers::Vertex));
	p_transform = reinterpret_cast<float*>(glMapNamedBufferRange(m_vboId[Buffers::Transform],
		0,
		16 * GetSize(Buffers::Transform),
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
}

void GLBuffers::Release()
{
	glUnmapNamedBuffer(m_vboId[Buffers::Transform]);
	glDeleteBuffers(1, &m_vboId[Buffers::Vertex]);
}
