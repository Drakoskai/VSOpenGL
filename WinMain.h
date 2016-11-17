#pragma once

#define NOMINMAX
#include <Windows.h>
#include <cassert>

namespace WinMainParameters
{
	inline HINSTANCE GetHInstance() 
	{
		return static_cast<HINSTANCE>(GetModuleHandle(nullptr));
	}

	inline HINSTANCE GetHPrevInstance() 
	{
		return static_cast<HINSTANCE>(nullptr);
	}

	inline LPWSTR GetLPCmdLine() {
		bool isQuoted = false;
		const wchar_t space = L' ';
		const wchar_t quote = L'\"';
		const wchar_t nullTerminator = L'\0';

		LPWSTR lpCmdLine = ::GetCommandLineW();
		assert(lpCmdLine != nullptr);

		while (*lpCmdLine <= space || isQuoted) {
			if (*lpCmdLine == quote) {
				isQuoted = !isQuoted;
			}
			lpCmdLine++;
		}

		while (*lpCmdLine <= space && *lpCmdLine != nullTerminator) {
			lpCmdLine++;
		}

		return lpCmdLine;
	}

	inline int GetNCmdShow() {
		::STARTUPINFOW startupInfo;
		::GetStartupInfoW(&startupInfo);
		if ((startupInfo.dwFlags & STARTF_USESHOWWINDOW) != 0) {
			return startupInfo.wShowWindow;
		}
		return SW_SHOWDEFAULT;
	}
}