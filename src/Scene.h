#pragma once

#include "Model/Object.h"
#include "InputHandler.h"
#include "GL/GLDevice.h"

class Scene
{
public:
	Scene(OpenGL::GLDevice& device, SimpleTimer& timer, InputHandler& input);
	~Scene();
	Model::Object& AddObjectToScene(const char* filename);
	void Frame();

private:
	OpenGL::GLDevice& m_device;
	SimpleTimer& m_timer;
	InputHandler& m_input;
	std::vector<Model::Object*> m_objects;

};
