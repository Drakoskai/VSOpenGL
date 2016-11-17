#include "GLDrawContext.h"
#include <vector>

class GLDrawContext::Impl
{
public:
	Impl(GLDeviceResources* gl);
	~Impl();

	void BeginScene() const;
	void DrawIndirect() const;
	void EndScene() const;
private:
	GLDeviceResources* m_gl;
	int m_vaoId;
	int m_voaName[1];
	float m_clearColor[4];
	float m_clearDepth;
};

GLDrawContext::GLDrawContext() : impl_(nullptr) { }

GLDrawContext::GLDrawContext(GLDeviceResources* gl)
	: impl_(new Impl(gl)) { }

GLDrawContext::~GLDrawContext() { }

void GLDrawContext::BeginScene() const
{
	impl_->BeginScene();
}

void GLDrawContext::DrawIndirect() const
{
	impl_->DrawIndirect();
}

void GLDrawContext::EndScene() const
{
	impl_->EndScene();
}

GLDrawContext::Impl::Impl(GLDeviceResources* gl)
	: m_gl(gl),
	m_vaoId(0),
	m_clearDepth(1.0f)
{
	m_clearColor[0] = 0.0f;
	m_clearColor[1] = 0.0f;
	m_clearColor[2] = 0.0f;
	m_clearColor[3] = 0.0f;
}

GLDrawContext::Impl::~Impl() { }

void GLDrawContext::Impl::BeginScene() const
{
	glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
	glClearDepth(m_clearDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDrawContext::Impl::DrawIndirect() const { }

void GLDrawContext::Impl::EndScene() const
{
	SwapBuffers(m_gl->GetDeviceContext());
}
