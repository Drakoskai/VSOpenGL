#pragma once

#include <vector>
#include <GL/glew.h>
#include <iostream>

namespace Util
{
	std::wstring StringToWString(const std::string& s);

	char* concat(char dest[], char src[]);

	void split(const std::string& s, char delim, std::vector<std::string>& elems);

	std::vector<std::string> split(const std::string& s, char delim);

	void ReadObjFile(std::string filename);

}