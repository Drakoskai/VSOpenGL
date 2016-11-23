#pragma once

#include "Transform.h"
#include <vector>
#include "GLDrawContext.h"
#include "Mesh.h"

class GLDrawContext;

class Model
{
public:

	Model(const std::string& filename);
	Model(float* vertexData, int vertexCount, int* elementData, int elementCount);
	~Model();
	void Init(GLDrawContext& dc);
	Transform GetTransform() const;
	void Update(float dt);
	void Draw(const GLDrawContext& dc) const;
	void Release() const;

private:
	std::string m_filename;
	Transform m_transform;
	Mesh * m_mesh;

};
