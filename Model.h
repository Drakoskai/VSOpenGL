#pragma once

#include "Transform.h"
#include "VertexBufferObject.h"

class Model
{
public:
	Model(const char* filename);
	~Model();
	
	Transform& GetTransform();
	void Update(const Matrix& proj);
	void Draw() const;

private:
	enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };
	bool Init();
	Transform m_transform;

	GLuint m_shaderProg;
	GLint m_uniformMVP;
	GLint m_uniformModelView;

	VertexBufferObject m_object;
};
