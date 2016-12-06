#include "../pch.h"
#include "Util.h"

namespace Util {

	std::wstring StringToWString(const std::string& s)
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

	char* concat(char dest[], char src[])
	{
		int i = 0;
		int j = 0;
		while (dest[i]) { ++i; }
		while (src[j]) { dest[i++] = src[j++]; }
		dest[i] = '\0';

		return dest;
	}

	void split(const std::string& s, char delim, std::vector<std::string>& elems)
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

	int VDebugPrintF(const char* format, va_list argList)
	{
		const unsigned int MAX_CHARS = 1024;
		static char s_buffer[MAX_CHARS];
		int charsWritten = vsnprintf_s(s_buffer, MAX_CHARS, format, argList);
		OutputDebugString(StringToWString(s_buffer).c_str());

		return charsWritten;
	}

	int DebugPrintF(const char* format, ...)
	{
		va_list argList;
		va_start(argList, format);
		int charsWritten = VDebugPrintF(format, argList);
		va_end(argList);

		return charsWritten;
	}
}
