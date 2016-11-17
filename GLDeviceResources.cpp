#include "GLDeviceResources.h"

GLDeviceResources::GLDeviceResources():
m_deviceContext(nullptr),
m_renderingContext(nullptr),
wglChoosePixelFormatARB(nullptr),
wglCreateContextAttribsARB(nullptr),
wglSwapIntervalEXT(nullptr), 
glAttachShader(nullptr), 
glBindBuffer(nullptr), 
glBindVertexArray(nullptr), 
glBufferData(nullptr), 
glCompileShader(nullptr),
glCreateProgram(nullptr), 
glCreateShader(nullptr), 
glDeleteBuffers(nullptr),
glDeleteProgram(nullptr), 
glDeleteShader(nullptr),
glDeleteVertexArrays(nullptr),
glDetachShader(nullptr), 
glEnableVertexAttribArray(nullptr),
glGenBuffers(nullptr), 
glGenVertexArrays(nullptr), 
glGetAttribLocation(nullptr), 
glGetProgramInfoLog(nullptr), 
glGetProgramiv(nullptr), 
glGetShaderInfoLog(nullptr),
glGetShaderiv(nullptr), 
glLinkProgram(nullptr), 
glShaderSource(nullptr),
glUseProgram(nullptr),
glVertexAttribPointer(nullptr), 
glBindAttribLocation(nullptr), 
glGetUniformLocation(nullptr), 
glUniformMatrix4fv(nullptr), 
glActiveTexture(nullptr), 
glUniform1i(nullptr), 
glGenerateMipmap(nullptr),
glDisableVertexAttribArray(nullptr), 
glUniform3fv(nullptr), 
glUniform4fv(nullptr) { }

GLDeviceResources::~GLDeviceResources() { }

bool GLDeviceResources::Init(HWND hwnd)
{		
	HDC deviceContext = { nullptr };
	deviceContext = GetDC(hwnd);
	if (!deviceContext)
	{
		return false;
	}
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}

	HGLRC renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}

	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	bool result = LoadExtensionList();
	if (!result)
	{
		return false;
	}

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);

	ReleaseDC(hwnd, deviceContext);

	return true;
}

void GLDeviceResources::Release(HWND hwnd)
{
	if (m_renderingContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = nullptr;
	}

	if (m_deviceContext)
	{
		ReleaseDC(hwnd, m_deviceContext);
		m_deviceContext = nullptr;
	}
}

void GLDeviceResources::BeginScene(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDeviceResources::EndScene() const
{
	SwapBuffers(m_deviceContext);
}

void GLDeviceResources::GetWorldMatrix(float* matrix)
{
	matrix[0] = m_worldMatrix[0];
	matrix[1] = m_worldMatrix[1];
	matrix[2] = m_worldMatrix[2];
	matrix[3] = m_worldMatrix[3];

	matrix[4] = m_worldMatrix[4];
	matrix[5] = m_worldMatrix[5];
	matrix[6] = m_worldMatrix[6];
	matrix[7] = m_worldMatrix[7];

	matrix[8] = m_worldMatrix[8];
	matrix[9] = m_worldMatrix[9];
	matrix[10] = m_worldMatrix[10];
	matrix[11] = m_worldMatrix[11];

	matrix[12] = m_worldMatrix[12];
	matrix[13] = m_worldMatrix[13];
	matrix[14] = m_worldMatrix[14];
	matrix[15] = m_worldMatrix[15];
}

void GLDeviceResources::GetProjMatrix(float* matrix)
{
	matrix[0] = m_projectionMatrix[0];
	matrix[1] = m_projectionMatrix[1];
	matrix[2] = m_projectionMatrix[2];
	matrix[3] = m_projectionMatrix[3];

	matrix[4] = m_projectionMatrix[4];
	matrix[5] = m_projectionMatrix[5];
	matrix[6] = m_projectionMatrix[6];
	matrix[7] = m_projectionMatrix[7];

	matrix[8] = m_projectionMatrix[8];
	matrix[9] = m_projectionMatrix[9];
	matrix[10] = m_projectionMatrix[10];
	matrix[11] = m_projectionMatrix[11];

	matrix[12] = m_projectionMatrix[12];
	matrix[13] = m_projectionMatrix[13];
	matrix[14] = m_projectionMatrix[14];
	matrix[15] = m_projectionMatrix[15];
}

void GLDeviceResources::BuildIdentityMatrix(float* matrix)
{
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void GLDeviceResources::BuildPerspectiveFovLHMatrix(float* matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth) const
{
	matrix[0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f / tan(fieldOfView * 0.5f);
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = screenDepth / (screenDepth - screenNear);
	matrix[11] = 1.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
	matrix[15] = 0.0f;
}

bool GLDeviceResources::InitOpenGL(HWND hwnd, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
{
	m_deviceContext = GetDC(hwnd);
	if (!m_deviceContext)
	{
		return false;
	}

	int attributeListInt[19];
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;
	attributeListInt[18] = 0;

	int pixelFormat[1];
	unsigned int formatCount;
	int result = wglChoosePixelFormatARB(m_deviceContext, attributeListInt, nullptr, 1, pixelFormat, &formatCount);
	if (result != 1)
	{
		return false;
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
	if (result != 1)
	{
		return false;
	}

	int attributeList[5];
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;
	attributeList[4] = 0;

	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, nullptr, attributeList);
	if (m_renderingContext == nullptr)
	{
		return false;
	}

	result = wglMakeCurrent(m_deviceContext, m_renderingContext);
	if (result != 1)
	{
		return false;
	}

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	BuildIdentityMatrix(m_worldMatrix);

	float fieldOfView = 3.14159265358979323846f / 4.0f;
	float screenAspect = (float)screenWidth / (float)screenHeight;

	BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	char *vendorString = (char*)glGetString(GL_VENDOR);
	char *rendererString = (char*)glGetString(GL_RENDERER);

	if (vsync)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	if (result != 1)
	{
		return false;
	}

	return true;
}

bool GLDeviceResources::LoadExtensionList()
{
	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
	if (!wglChoosePixelFormatARB)
	{
		return false;
	}

	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	if (!wglCreateContextAttribsARB)
	{
		return false;
	}

	wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
	if (!wglSwapIntervalEXT)
	{
		return false;
	}

	glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));
	if (!glAttachShader)
	{
		return false;
	}

	glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));
	if (!glBindBuffer)
	{
		return false;
	}

	glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
	if (!glBindVertexArray)
	{
		return false;
	}

	glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));
	if (!glBufferData)
	{
		return false;
	}

	glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));
	if (!glCompileShader)
	{
		return false;
	}

	glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));
	if (!glCreateProgram)
	{
		return false;
	}

	glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
	if (!glCreateShader)
	{
		return false;
	}

	glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(wglGetProcAddress("glDeleteBuffers"));
	if (!glDeleteBuffers)
	{
		return false;
	}

	glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(wglGetProcAddress("glDeleteProgram"));
	if (!glDeleteProgram)
	{
		return false;
	}

	glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(wglGetProcAddress("glDeleteShader"));
	if (!glDeleteShader)
	{
		return false;
	}

	glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(wglGetProcAddress("glDeleteVertexArrays"));
	if (!glDeleteVertexArrays)
	{
		return false;
	}

	glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(wglGetProcAddress("glDetachShader"));
	if (!glDetachShader)
	{
		return false;
	}

	glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glEnableVertexAttribArray"));
	if (!glEnableVertexAttribArray)
	{
		return false;
	}

	glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));
	if (!glGenBuffers)
	{
		return false;
	}

	glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));
	if (!glGenVertexArrays)
	{
		return false;
	}

	glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(wglGetProcAddress("glGetAttribLocation"));
	if (!glGetAttribLocation)
	{
		return false;
	}

	glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(wglGetProcAddress("glGetProgramInfoLog"));
	if (!glGetProgramInfoLog)
	{
		return false;
	}

	glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));
	if (!glGetProgramiv)
	{
		return false;
	}

	glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(wglGetProcAddress("glGetShaderInfoLog"));
	if (!glGetShaderInfoLog)
	{
		return false;
	}

	glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));
	if (!glGetShaderiv)
	{
		return false;
	}

	glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(wglGetProcAddress("glLinkProgram"));
	if (!glLinkProgram)
	{
		return false;
	}

	glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));
	if (!glShaderSource)
	{
		return false;
	}

	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
	if (!glUseProgram)
	{
		return false;
	}

	glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));
	if (!glVertexAttribPointer)
	{
		return false;
	}

	glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(wglGetProcAddress("glBindAttribLocation"));
	if (!glBindAttribLocation)
	{
		return false;
	}

	glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(wglGetProcAddress("glGetUniformLocation"));
	if (!glGetUniformLocation)
	{
		return false;
	}

	glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(wglGetProcAddress("glUniformMatrix4fv"));
	if (!glUniformMatrix4fv)
	{
		return false;
	}

	glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(wglGetProcAddress("glActiveTexture"));
	if (!glActiveTexture)
	{
		return false;
	}

	glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(wglGetProcAddress("glUniform1i"));
	if (!glUniform1i)
	{
		return false;
	}

	glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(wglGetProcAddress("glGenerateMipmap"));
	if (!glGenerateMipmap)
	{
		return false;
	}

	glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glDisableVertexAttribArray"));
	if (!glDisableVertexAttribArray)
	{
		return false;
	}

	glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(wglGetProcAddress("glUniform3fv"));
	if (!glUniform3fv)
	{
		return false;
	}

	glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(wglGetProcAddress("glUniform4fv"));
	if (!glUniform4fv)
	{
		return false;
	}

	return true;
}
