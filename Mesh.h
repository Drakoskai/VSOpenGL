#pragma once
#include "GLBuffers.h"
#include "Transform.h"
#include <vector>

class Mesh
{
public:
	Mesh(std::vector<Vector3f>& vertices, std::vector<unsigned int>& elements, GLint elementType);
	~Mesh();
	void Init(const GLDrawContext& dc);
	void Update(Transform& transform) const;
	void Draw(const GLDrawContext& dc);
	void Release() const;

	void SetShader(GLuint shaderProgram);

private:
	GLBuffers m_buffers;	
	unsigned int * vboName;
	GLuint m_shaderProgram;
	float * m_transformPointer;

};
