#pragma once

#include "Transform.h"
#include <vector>
#include "DrawContext.h"

class DrawContext;

class Model
{
public:
	Model(float** vertices, int numVerts, GLint*** elements, int numElements, int numPerFace);
	~Model();
	void Init(DrawContext& dc);
	Transform GetTransform() const;
	void Update(const Matrix& proj);
	void Draw() const;
	void Release() const;

private:
	enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };

	Transform m_transform;
	GLuint m_vao;
	GLuint m_shaderProg;
	GLint m_vPosition;
	GLuint m_PersLoc;
	GLint m_modelViewLoc;
	GLuint * m_buffers;

	int m_numVerts;
	int m_numElements;
	int m_numPerFace;

	GLfloat m_tessInner = 10.0f;
	GLfloat  m_tessOuter = 10.0f;

	GLuint m_UniInnerLoc;
	GLuint m_UniOuterLoc;

	float ** m_vertices;
	GLint *** m_elements;

};
