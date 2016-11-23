#include "Model.h"
#include <vector>
#include "ObjFile.h"
#include <iostream>
#include <GL/glew.h>
#include "GLSemantic.h"


Model::Model(const std::string& filename)
	: m_filename(filename), m_mesh(nullptr) { }

Model::Model(float* vertexData, int vertexCount, int* elementData, int elementCount)
{
}

Model::~Model() { Release(); }

void Model::Init(GLDrawContext& dc)
{
	ObjFile file = ObjFile(m_filename);
	std::vector<Vector3f> vertices;
	std::vector<Vector2f> uvs;
	std::vector<Vector3f> normals;
	std::vector<unsigned int> indices;
	file.GetMeshData(vertices, uvs, normals, indices);

	m_mesh = new Mesh(vertices, indices, GL_TRIANGLES);

	GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLenum GLerror;
	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "GL error: %x\n", GLerror);
	}

	GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "GL error: %x\n", GLerror);
	}

	std::string	vertShaderSrc = dc.LoadShaderFromFile("test.vert");
	std::string	fragShaderSrc = dc.LoadShaderFromFile("test.frag");

	const char * vertShaderBuffer = vertShaderSrc.c_str();
	GLint  vertShaderLength = vertShaderSrc.size();
	const char * fragShaderBuffer = vertShaderSrc.c_str();
	GLint const fragshaderLength = vertShaderSrc.size();

	glShaderSource(vertShaderId, 1, &vertShaderBuffer, &vertShaderLength);

	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "GL error: %x\n", GLerror);
	}

	glShaderSource(fragShaderId, 1, &fragShaderBuffer, &fragshaderLength);
	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "GL error: %x\n", GLerror);
	}

	glCompileShader(vertShaderId);
	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "GL error: %x\n", GLerror);
	}

	glCompileShader(fragShaderId);
	if ((GLerror = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "GL error: %x\n", GLerror);
	}

	GLint status = 0;

	glGetShaderiv(vertShaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		dc.OutputShaderErrorMessage(vertShaderId, "test.vert");
	}

	glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		dc.OutputShaderErrorMessage(fragShaderId, "test.frag");
	}

	GLuint shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShaderId);
	glAttachShader(shaderProg, fragShaderId);
	glLinkProgram(shaderProg);

	delete[] fragShaderBuffer;
	delete[] vertShaderBuffer;
}

Transform Model::GetTransform() const { return m_transform; }

void Model::Update(float dt) { m_mesh->Update(m_transform); }

void Model::Draw(const GLDrawContext& dc) const
{
	m_mesh->Draw(dc);
}

void Model::Release() const
{
	if (m_mesh)
	{
		m_mesh->Release();
		delete m_mesh;
	}
}
