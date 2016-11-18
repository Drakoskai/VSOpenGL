#include "Cube.h"

Cube::Cube()
	: m_height(0), m_width(1.0f), m_depth(1.0f), m_shaderProgram(0) { }

Cube::Cube(float h, float w, float d)
	: m_height(h), m_width(w), m_depth(d), m_shaderProgram(0) { }

Cube::~Cube() { }

void Cube::Init(GLDrawContext * dc)
{
	m_buffers.InitBuffers(dc);
}

Transform Cube::GetTransform() { return m_transform; }

void Cube::Update(float dt) { }

void Cube::Release()
{
	m_buffers.Release();
}
