#include "GLDrawContext.h"
#include <vector>
#include <GL/glew.h>
#include <fstream>
#include "Util.h"

class GLDrawContext::Impl
{
public:
	Impl(GLDeviceResources* gl);
	~Impl();
	void Init();
	void BeginScene() const;
	void Draw() const;
	void EndScene() const;
	unsigned int GetVaoId() const;
	GLDeviceResources *	GetGL() const;
	static unsigned int LoadShader(std::string filename);
	static void OutputShaderErrorMessage(unsigned int shaderId, char* shaderFilename);

private:
	static std::string LoadShaderFromFile(std::string filename);
	GLDeviceResources* m_gl;
	GLuint m_vaoId;
	int m_voaName[1];
	float m_clearColor[4];
	float m_clearDepth;
};

GLDrawContext::GLDrawContext() : impl_(nullptr) { }

GLDrawContext::GLDrawContext(GLDeviceResources* gl)
	: impl_(new Impl(gl)) { }

GLDrawContext::~GLDrawContext() { }

void GLDrawContext::Init() const
{
	impl_->Init();
}

void GLDrawContext::BeginScene() const
{
	impl_->BeginScene();
}

void GLDrawContext::Draw() const
{
	impl_->Draw();
}

void GLDrawContext::EndScene() const
{
	impl_->EndScene();
}

unsigned int GLDrawContext::GetVaoId() const
{
	return impl_->GetVaoId();
}

GLDeviceResources* GLDrawContext::GetGL() const
{
	return impl_->GetGL();
}

unsigned int GLDrawContext::LoadShader(std::string filename) const
{
	return impl_->LoadShader(filename);
}

GLDrawContext::Impl::Impl(GLDeviceResources* gl)
	: m_gl(gl),	m_vaoId(0),	m_clearDepth(1.0f)
{
	m_clearColor[0] = 0.0f;
	m_clearColor[1] = 0.0f;
	m_clearColor[2] = 0.0f;
	m_clearColor[3] = 0.0f;
}

GLDrawContext::Impl::~Impl()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vaoId);
}

void GLDrawContext::Impl::Init()
{
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
}

void GLDrawContext::Impl::BeginScene() const
{
	glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
	glClearDepth(m_clearDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDrawContext::Impl::Draw() const { }

void GLDrawContext::Impl::EndScene() const
{
	SwapBuffers(m_gl->GetDeviceContext());
}

unsigned GLDrawContext::Impl::GetVaoId() const
{
	return m_vaoId;
}

GLDeviceResources* GLDrawContext::Impl::GetGL() const
{
	return m_gl;
}

unsigned int GLDrawContext::Impl::LoadShader(std::string filename)
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

std::string GLDrawContext::Impl::LoadShaderFromFile(std::string filename)
{
	FILE* f = nullptr;
	fopen_s(&f, filename.c_str(), "r");
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	char* buffer = new char[size +1];
	rewind(f);
	fread(buffer, sizeof(char), size, f);
	buffer[size] = '\0';

	std::string outstr(buffer);
	delete[] buffer;

	return outstr;
}

char * concat(char dest[], char src[])
{
	int i = 0, j = 0;
	while (dest[i]) ++i;
	while (src[j]) dest[i++] = src[j++];
	dest[i] = '\0';
	return dest;
}

void  GLDrawContext::Impl::OutputShaderErrorMessage(unsigned int shaderId, char* shaderFilename)
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