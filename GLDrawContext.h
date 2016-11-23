#pragma once

#include "GLDevice.h"
#include <string>
#include "Interfaces.h"
#include "GLWindow.h"

class Model;

class GLDrawContext : DrawContext
{
public:
	GLDrawContext();
	~GLDrawContext();

	void Init() override;
	void BeginScene() override;
	void Draw() const override;
	void EndScene() const override;
	Window* GetWindow() override;
	unsigned int GetVaoId() const;
	void GetWorldMatrix(Matrix& matrix) const;
	void Release() const;

	unsigned int LoadShader(std::string filename, GLuint type);
	void OutputShaderErrorMessage(unsigned int shaderId, std::string shaderFilename);
	std::string LoadShaderFromFile(std::string filename);

private:
	DisplayState m_currentDisplayState;
	GLuint m_vaoId;
	int m_voaName[1];
	GLfloat m_clearColor[4];
	float m_clearDepth;
	HWND m_hWnd;
	GLDevice* m_gl;
	GLWindow* m_window;

	Matrix m_worldMatrix;
	Matrix m_projectionMatrix;
};
