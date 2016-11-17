#pragma once

#include "GLDeviceResources.h"
#include <memory>
#include <vector>

class Model;

class GLDrawContext
{
	class Impl;
public:
	GLDrawContext(GLDeviceResources * gl);
	~GLDrawContext();

	void BeginScene() const;
	void DrawIndirect() const;
	void EndScene() const;

	int LoadShader(std::string filename);

private:
	GLDrawContext();
	unsigned int CompileShader(char* shaderCode);
	std::unique_ptr<Impl>  impl_;
};
