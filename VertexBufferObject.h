#pragma once

#include "Vector.h"

struct VBOInfo
{
	unsigned int size;
	unsigned int numAttribs;
	unsigned int numVertices;
	unsigned int numIndices;
};

class VertexBufferObject
{
public:
	VertexBufferObject();
	~VertexBufferObject();
	void Load(const char * filename);
	void Render() const;
	void Release();

private:
	GLuint m_vao;
	GLuint m_attributeBuffer;
	GLuint m_indexBuffer;

	VBOInfo m_info;
};
