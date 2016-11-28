#pragma once

#include "Transform.h"
#include <vector>
#include "GLDrawContext.h"

class GLDrawContext;

class Model
{
public:

	Model(const std::string& filename);
	~Model();
	void Init(GLDrawContext& dc);
	Transform GetTransform() const;
	void Update(float dt);
	void Draw(const GLDrawContext& dc) const;
	void Release() const;

private:
	std::string m_filename;
	Transform m_transform;
	GLuint m_shaderProg;
};
