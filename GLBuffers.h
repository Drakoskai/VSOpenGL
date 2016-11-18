#pragma once
#include "GLDrawContext.h"

namespace Buffers
{
	enum GLBuffer
	{
		Vertex = 0,
		Element = 1,
		Normal = 2,
		Transform = 3,
		Name = 4
	};
}

class GLBuffers
{

public:
	GLBuffers();
	~GLBuffers();

	int GetMode(Buffers::GLBuffer type);
	void SetMode(Buffers::GLBuffer type, int mode);
	int GetCount(Buffers::GLBuffer type);
	unsigned int GetSize(Buffers::GLBuffer type);
	int GetGLType(Buffers::GLBuffer type);
	unsigned int GetId(Buffers::GLBuffer type);
	unsigned int GetStride(Buffers::GLBuffer type);

	void SetElementData(int mode, int * src, unsigned int numElements);
	void SetVertexData(float * src, unsigned int numVerts);
	void SetNormalData(float * src, unsigned int numNormals);

	void InitBuffers(GLDrawContext * dc);
	void Release();

private:
	int m_mode[4];
	unsigned int m_vboId[4];
	unsigned int m_count[4];
	unsigned int m_size[4];
	unsigned int m_stride[4];
	unsigned int m_glType[4];
	unsigned int m_shaderProgram;


	float * m_vertexData;
	float * m_normalData;
	int * m_elementData;
	float * p_transform;
};