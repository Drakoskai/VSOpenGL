#pragma once

#include "GLDeviceResources.h"
#include <memory>
#include <string>

class Model;

class GLDrawContext
{
	class Impl;
public:
	GLDrawContext(GLDeviceResources * gl);
	~GLDrawContext();

	void Init() const;
	void BeginScene() const;
	void Draw() const;
	void EndScene() const;
	unsigned int GetVaoId() const;
	GLDeviceResources * GetGL() const;
	unsigned int LoadShader(std::string filename) const;

private:
	GLDrawContext();
	std::unique_ptr<Impl>  impl_;
};
