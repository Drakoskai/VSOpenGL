#include "TestTriangle.h"
#include <GL/glew.h>
#include "GLDrawContext.h"

TestTriangle::TestTriangle()
	: m_vertexCount(0), m_indexCount(0), m_vertexArrayId(0), m_vertexBufferId(0), m_indexBufferId(0), m_shaderProgram(0)
{
}

TestTriangle::~TestTriangle() { }

void TestTriangle::Init()
{
	m_vertexCount = 3;
	m_indexCount = 3;
	
	VertexType* vertices = new VertexType[m_vertexCount];	

	vertices[0].x = -1.0f;
	vertices[0].y = -1.0f;
	vertices[0].z = 0.0f;

	vertices[0].r = 0.0f; 
	vertices[0].g = 1.0f;
	vertices[0].b = 0.0f;
	
	vertices[1].x = 0.0f;
	vertices[1].y = 1.0f;
	vertices[1].z = 0.0f;

	vertices[1].r = 0.0f;
	vertices[1].g = 1.0f;
	vertices[1].b = 0.0f;

	vertices[2].x = 1.0f;  
	vertices[2].y = -1.0f;
	vertices[2].z = 0.0f;

	vertices[2].r = 0.0f; 
	vertices[2].g = 1.0f;
	vertices[2].b = 0.0f;

	unsigned int* indices= new unsigned int[m_indexCount];

	indices[0] = 0;  
	indices[1] = 1;  
	indices[2] = 2;  


	GLuint vertShaderid = GLDrawContext::LoadShader("test.vert");
	GLuint fragShaderid = GLDrawContext::LoadShader("test.frag");

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertShaderid);
	glAttachShader(m_shaderProgram, fragShaderid);
	glLinkProgram(m_shaderProgram);


	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);
	glGenBuffers(1, &m_vertexBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1); 
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexType), static_cast<unsigned char*>(nullptr) + 3 * sizeof(float));


	glGenBuffers(1, &m_indexBufferId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount* sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	delete[] vertices;
	delete[] indices;
}

void TestTriangle::Draw() const
{
	glBindVertexArray(m_vertexArrayId);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
}

void TestTriangle::Release() const
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vertexBufferId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_indexBufferId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vertexArrayId);
}
