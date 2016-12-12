#include "pch.h"
#include "Scene.h"

Scene::Scene(OpenGL::GLDevice& device, SimpleTimer& timer, InputHandler& input)
: m_device(device), m_timer(timer), m_input(input) { }

Scene::~Scene() { }

Model::Object& Scene::AddObjectToScene(const char* filename)
{
	Model::Object* obj = new Model::Object(filename);
	m_objects.push_back(obj);

	return *obj;
}

void Scene::Frame()
{
	m_device.BeginScene();

	for (auto&& drawable : m_objects) { drawable->Draw(); }

	m_device.EndScene();
}
