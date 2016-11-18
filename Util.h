#pragma once
#include <string>
#include <winnls.h>

namespace Util
{
	inline std::wstring StringToWString(const std::string& s)
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

	inline char * concat(char dest[], char src[])
	{
		int i = 0;
		int j = 0;
		while (dest[i]){ ++i; }
		while (src[j]){ dest[i++] = src[j++]; }
		dest[i] = '\0';
		return dest;
	}
}
