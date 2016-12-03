#pragma once

#include "Transform.h"
#include <vector>
#include "VertexBufferObject.h"

class Model
{
public:
	Model(const char* filename);
	~Model();
	void Init();
	Transform& GetTransform();
	void Update(const Matrix& proj);
	void Draw() const;
	void Release();

private:
	enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };

	Transform m_transform;

	GLuint m_shaderProg;
	GLint m_uniformMVP;
	GLint m_uniformModelView;

	VertexBufferObject m_object;
};
