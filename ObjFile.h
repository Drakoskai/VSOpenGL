#pragma once

#include <vector>
#include "Vector.h"

class ObjFile
{
	
public:	
	ObjFile(std::string filename);
	~ObjFile();

	bool Exists();
	void GetVertices(std::vector<Vector3f>& vertices);
	void GetNormals(std::vector<Vector3f>& normals);
	void GetUVs(std::vector<Vector2f>& uvs);
	std::string ToString();

private:
	void LoadData();
	bool m_exists;
	bool m_isLoaded;

	std::string m_filename;
	std::vector<Vector3f> m_verts;
	std::vector<Vector3f> m_normals;
	std::vector<Vector2f> m_uvs;

};
