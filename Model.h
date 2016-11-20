#pragma once

#include "Interfaces.h"
#include "Transform.h"
#include <string>
#include <vector>
#include <GL/glew.h>
#include "GLDrawContext.h"

class GLDrawContext;

class Model
{
public:

	Model(const std::string& filename);
	~Model();
	void Init(GLDrawContext * dc);
	Transform GetTransform();
	void Update(float dt);
	void Draw();
	void Release();

private:
	std::string m_filename;
	GLuint m_vaoId;
	GLuint m_vboid;
	GLuint m_idxid;
	GLuint m_transformid;
	GLuint m_shaderProgram;

	Transform m_transform;
	std::vector<Vector3f> m_vertexData;
	std::vector<Vector3f> m_normalData;
	std::vector<Vector2f> m_uvData;
	std::vector<unsigned short> m_idxData;

	float * m_transformPointer;


};
