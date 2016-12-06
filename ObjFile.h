#pragma once

#include <vector>
#include "Vector.h"
#include "Vertex.h"

class ObjFile
{
	
public:	
	ObjFile(std::string filename);
	~ObjFile();

	bool Exists();
	void GetVertices(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	std::string ToString();

private:
	void LoadData();

	bool m_exists;
	bool m_isLoaded;

	std::string m_filename;
	std::vector<Vector3f> m_positions;
	std::vector<Vector3f> m_normals;
	std::vector<Vector2f> m_uvs;
	std::vector<GLuint> m_vertIndices;
	std::vector<GLuint> m_normalIndices;
	std::vector<GLuint> m_uvIndices;
};
