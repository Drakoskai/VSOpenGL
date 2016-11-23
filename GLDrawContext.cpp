#include "GLDrawContext.h"
#include <vector>
#include <GL/glew.h>
#include <fstream>
#include "Util.h"
#include "GLWindow.h"
#include <iostream>
#include "GLSemantic.h"

GLDrawContext::GLDrawContext()
	: m_vaoId(0), m_clearDepth(0), m_hWnd(nullptr), m_gl(nullptr), m_window(nullptr)
{
	m_clearColor[0] = 0.0f;
	m_clearColor[1] = 0.0f;
	m_clearColor[2] = 0.0f;
	m_clearColor[3] = 0.0f;
}

GLDrawContext::~GLDrawContext()
{
	m_gl->Release(m_hWnd);
	delete m_gl;
	m_gl = nullptr;

	delete m_window;
	m_window = nullptr;
}

void GLDrawContext::Init()
{
	m_window = new GLWindow();
	m_gl = new GLDevice();
	m_currentDisplayState = {};
	m_hWnd = m_window->Create(m_currentDisplayState);
	m_gl->Init(m_hWnd);
	m_gl->InitOpenGL(m_hWnd, m_currentDisplayState);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glCreateVertexArrays(1, &m_vaoId);

	glVertexArrayAttribBinding(m_vaoId, Semantic::Attr::Position, Semantic::Stream::_0);
	//glVertexArrayAttribBinding(m_vaoId, Semantic::Attr::Color, Semantic::Stream::_0);

	glVertexArrayAttribFormat(m_vaoId, Semantic::Attr::Position, 3, GL_FLOAT, false, 0);
	//glVertexArrayAttribFormat(m_vaoId, Semantic::Attr::Color, 3, GL_FLOAT, false, 2 * sizeof(float));

	glEnableVertexArrayAttrib(m_vaoId, Semantic::Attr::Position);
	//glEnableVertexArrayAttrib(m_vaoId, Semantic::Attr::Color);

}

void GLDrawContext::BeginScene()
{
	glClearBufferfv(GL_COLOR, 0,  m_clearColor);
	glClearBufferfv(GL_DEPTH, 0, &m_clearDepth);
}

void GLDrawContext::Draw() const
{
}

void GLDrawContext::EndScene() const
{
	SwapBuffers(m_gl->GetDeviceContext());
}

void GLDrawContext::GetWorldMatrix(Matrix& matrix) const
{
	matrix = m_worldMatrix;
}

void GLDrawContext::Release() const
{
	glDeleteVertexArrays(1, &m_vaoId);
}

Window* GLDrawContext::GetWindow()
{
	return reinterpret_cast<Window*>(m_window);
}

unsigned int GLDrawContext::LoadShader(std::string filename, GLuint type)
{
	std::string	shaderCode = LoadShaderFromFile(filename);
	GLuint shader = glCreateShader(type); 
	GLchar const * shaderBuffer = shaderCode.c_str();
	GLint const shaderLength = shaderCode.size();
	glShaderSource(shader, 1, &shaderBuffer, NULL);
	glCompileShader(shader);
	GLint status = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		OutputShaderErrorMessage(shader, filename);
	}

	return shader;
}

unsigned int GLDrawContext::GetVaoId() const
{
	return m_vaoId;
}

std::string GLDrawContext::LoadShaderFromFile(std::string filename)
{
	std::ifstream ifile(filename);
	std::string outstr;
	getline(ifile, outstr, '\0');

	return outstr;
}

void  GLDrawContext::OutputShaderErrorMessage(unsigned int shaderId, std::string shaderFilename)
{
	int logSize = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	GLchar* infoLog;
	infoLog = new GLchar[logSize+1];
	glGetShaderInfoLog(shaderId, logSize, &logSize, infoLog);
	fprintf(stderr, "Compiler/Linker error: %s\n", infoLog);

	std::wstring msg = L"Error compiling shader. " + Util::StringToWString(shaderFilename);
	MessageBox(nullptr, msg.c_str(), Util::StringToWString(infoLog).c_str(), MB_OK);

	delete[] infoLog;
}