#pragma once

#include <vector>

template<typename T>
void SafeDelete(T* ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template<typename T>
void SafeDeleteArr(T* ar)
{
	if (ar)
	{
		delete[] ar;
		ar = nullptr;
	}
}

template <typename T>
void* BfrStorage(const T& t)
{
	return reinterpret_cast<void*>(t);
}

namespace Util
{
	static const bool IsDebug = true;

	std::wstring StringToWString(const std::string& s);

	char* concat(char dest[], char src[]);

	void split(const std::string& s, char delim, std::vector<std::string>& elems);

	std::vector<std::string> split(const std::string& s, char delim);

	int VDebugPrintF(const char* format, va_list argList);

	int DebugPrintF(const char* format, ...);
}