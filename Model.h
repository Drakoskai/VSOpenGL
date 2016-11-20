#pragma once

#include "Interfaces.h"
#include "Transform.h"
#include <string>
#include <vector>

class Model
{
public:
	Model(const std::string& filename);
	~Model();
	void Init(DrawContext * dc);
	Transform GetTransform();
	void Update(float dt);
	void Release();

private:
	Transform m_transform;
	std::vector<Vector3f> m_vertexData;
	std::vector<Vector3f> m_normalData;
	std::vector<Vector2f> m_uvData;

};
