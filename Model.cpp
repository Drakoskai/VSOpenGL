#include "Model.h"
#include <vector>
#include "ObjFile.h"


Model::Model(const std::string& filename)
	: m_filename(filename), m_shaderProg(0) { }

Model::~Model() { Release(); }

void Model::Init(GLDrawContext& dc)
{
	ObjFile file = ObjFile(m_filename);
	std::vector<Vector3f> vertices;
	std::vector<Vector2f> uvs;
	std::vector<Vector3f> normals;
	std::vector<unsigned int> indices;
	file.GetMeshData(vertices, uvs, normals, indices);
}

Transform Model::GetTransform() const { return m_transform; }

void Model::Update(float dt) {  }

void Model::Draw(const GLDrawContext& dc) const { }

void Model::Release() const { }
