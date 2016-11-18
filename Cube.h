#pragma once

#include "Model.h"
#include "GLBuffers.h"
#include "Transform.h"

class Cube : Model
{
public:
	Cube();
	Cube(float h, float w, float d);
	~Cube() override;

	void Init(GLDrawContext * dc) override;
	Transform GetTransform() override;
	void Update(float dt) override;
	void Release() override;

private:
	float m_height;
	float m_width;
	float m_depth;	
	unsigned int m_shaderProgram;
	GLuint m_vboName[5];
	GLBuffers m_buffers;
	Transform m_transform;
	static const float m_vertexData[];
	static const int m_elementData[];
};

const float Cube::m_vertexData[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f
};

const int Cube::m_elementData[] = {
	0, 1, 2, 2, 3, 0,
	3, 2, 6, 6, 7, 3,
	7, 6, 5, 5, 4, 7,
	4, 0, 3, 3, 7, 4,
	0, 1, 5, 5, 4, 0,
	1, 5, 6, 6, 2, 1
};
