#include "GLDrawContext.h"
#include <vector>
#include <GL/glew.h>
#include <fstream>
#include "Util.h"
#include "GLWindow.h"

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vaoId);

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
	m_currentDisplayState = { };
	m_hWnd = m_window->Create(m_currentDisplayState);
	m_gl->Init(m_hWnd);
	m_gl->InitOpenGL(m_hWnd, m_currentDisplayState);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	float fieldOfView = 3.14159265358979323846f / 4.0f;
	float screenAspect = static_cast<float>(m_currentDisplayState.ScreenWidth) / static_cast<float>(m_currentDisplayState.ScreenHeight);
	BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, m_currentDisplayState.ScreenNear, m_currentDisplayState.ScreenDepth);
}

void GLDrawContext::BeginScene() const
{
	glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
	glClearDepth(m_clearDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDrawContext::Draw() const { }

void GLDrawContext::EndScene() const
{
	SwapBuffers(m_gl->GetDeviceContext());
}

void GLDrawContext::BuildPerspectiveFovLHMatrix(Matrix& matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth) const
{
	matrix.Identity();
	matrix.mat[0].x /= (screenAspect * tan(fieldOfView * 0.5f));
	matrix.mat[1].y /= tan(fieldOfView * 0.5f);
	matrix.mat[2].z = screenDepth / (screenDepth - screenNear);
	matrix.mat[3].z = (-screenNear * screenDepth) / (screenDepth - screenNear);
	matrix.mat[4].w = 0.0f;
}

void GLDrawContext::GetWorldMatrix(Matrix& matrix) const
{
	matrix = m_worldMatrix;
}

void GLDrawContext::GetProjMatrix(Matrix& matrix) const
{
	matrix = m_projectionMatrix;
}

Window* GLDrawContext::GetWindow()
{
	return reinterpret_cast<Window*>(m_window);
}

unsigned int GLDrawContext::LoadShader(std::string filename)
{
	std::string	shaderCode = LoadShaderFromFile(filename + ".vert");
	GLint shader = glCreateShader(GL_VERTEX_SHADER);
	const char * shaderBuffer = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderBuffer, nullptr);
	glCompileShader(shader);
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	return shader;
}

unsigned int GLDrawContext::GetVaoId() const
{
	return m_vaoId;
}

std::string GLDrawContext::LoadShaderFromFile(std::string filename)
{
	FILE* f = nullptr;
	fopen_s(&f, filename.c_str(), "r");

	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	char* buffer = new char[size + 1];

	rewind(f);

	fread(buffer, sizeof(char), size, f);
	buffer[size] = '\0';

	std::string outstr(buffer);
	delete[] buffer;

	return outstr;
}

void  GLDrawContext::OutputShaderErrorMessage(unsigned int shaderId, char* shaderFilename)
{
	int logSize;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	GLchar* infoLog;
	logSize++;
	infoLog = new GLchar[logSize];
	glGetShaderInfoLog(shaderId, logSize, nullptr, infoLog);

	std::wstring msg = L"Error compiling shader. " + Util::StringToWString(shaderFilename);

	MessageBox(nullptr, msg.c_str(), Util::StringToWString(infoLog).c_str(), MB_OK);

	delete[] infoLog;
}