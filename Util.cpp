#include "Util.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

std::wstring Util::StringToWString(const std::string& s)
{
	int len;
	int slength = static_cast<int>(s.length()) + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;

	return r;
}

char* Util::concat(char dest[], char src[])
{
	int i = 0;
	int j = 0;
	while (dest[i]) { ++i; }
	while (src[j]) { dest[i++] = src[j++]; }
	dest[i] = '\0';

	return dest;
}

void Util::split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}

std::vector<std::string> Util::split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void Util::ReadObjFile(std::string filename)
{
	using namespace std;

	ifstream in;
	string s;
	in.open(filename.c_str());

	while (in)
	{
		getline(in, s);
		cout << s << endl;
	}
}
