#include "Model.h"
#include <vector>
#include "ObjFile.h"

Model::Model(const std::string& filename) 
{
	ObjFile file = ObjFile(filename);

	file.GetVertices(m_vertexData);
	file.GetNormals(m_normalData);
	file.GetUVs(m_uvData);
}

Model::~Model() { }

void Model::Init(DrawContext* dc) { }

Transform Model::GetTransform() { return m_transform; }

void Model::Update(float dt) { }

void Model::Release() { }
