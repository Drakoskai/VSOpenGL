#pragma once

#include <windows.h>
#include "Interfaces.h"

class GLWindow : Window
{
public:
	GLWindow();
	~GLWindow();

	HWND Create(const DisplayState &displayState) override;
	HWND GetWindowHandle() const;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WinMsgHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static GLWindow *GetViewFromObject(HWND hWnd)
	{
		return reinterpret_cast<GLWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

private:
	BOOL InitInstance(const DisplayState &displayState);
	ATOM GLRegisterClass() const;

	HINSTANCE m_hInst;
	HINSTANCE m_prevInst;
	LPWSTR m_lpCmdLine;
	int m_nCmdShow;
	HWND m_hWnd;

	TCHAR m_title[Display::MaxLoadString];
	TCHAR m_windowClass[Display::MaxLoadString];

};
