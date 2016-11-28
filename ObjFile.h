#pragma once

#include <vector>
#include "Vector.h"

class ObjFile
{
	
public:	
	ObjFile(std::string filename);
	~ObjFile();

	bool Exists();
	void GetMeshData(std::vector<Vector3f>& vertices, std::vector<Vector2f>& uvs, std::vector<Vector3f>& normals, std::vector<unsigned int>& indices);
	std::string ToString();

private:
	void LoadData();
	bool m_exists;
	bool m_isLoaded;

	std::string m_filename;
	std::vector<Vector3f> m_verts;
	std::vector<Vector3f> m_normals;
	std::vector<Vector2f> m_uvs;
	std::vector<int> m_vertIndices;
	std::vector<int> m_normalIndices;
	std::vector<int> m_uvIndices;
};
