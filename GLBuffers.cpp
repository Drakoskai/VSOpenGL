#include "GLBuffers.h"
#include <GL/glew.h>
#include <gl/gl.h>
#include "GLAttrib.h"
#include "GLSemantic.h"

GLBuffers::GLBuffers()
	: m_shaderProgram(0), m_vertexData(nullptr), m_normalData(nullptr),
	m_elementData(nullptr), p_transform(nullptr) { }

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

void GLBuffers::SetElementData(GLint mode, unsigned* src, unsigned numElements)
{
	m_elementData = src;
	m_mode[Buffers::Element] = mode;
	m_size[Buffers::Element] = numElements * sizeof(unsigned int);
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

float* GLBuffers::GetFloatBuffer(Buffers::GLBuffer type)
{
	if (type == Buffers::GLBuffer::Vertex)
	{
		return m_vertexData;
	}
	if (type == Buffers::GLBuffer::Normal)
	{
		return m_normalData;
	}
}

unsigned int* GLBuffers::GetIntBuffer(Buffers::GLBuffer type)
{
	return m_elementData;
}
