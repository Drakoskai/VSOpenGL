#pragma once

#include <windows.h>

class GLWindow
{
public:
	GLWindow();
	~GLWindow();
	void Create();
	
	HWND GetWindowHandle() const;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WinMsgHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static GLWindow *GetViewFromObject(HWND hWnd)
	{
		return reinterpret_cast<GLWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	static const int MaxLoadString = 100;
	static const int DefaultHeight = 1280;
	static const int DefaultWidth = 720;

private:
	BOOL InitInstance();
	ATOM GLRegisterClass() const;

	HINSTANCE m_hInst;
	HINSTANCE m_prevInst;
	LPWSTR m_lpCmdLine;
	int m_nCmdShow;
	HWND m_hWnd;

	TCHAR m_title[MaxLoadString];
	TCHAR m_windowClass[MaxLoadString];

	int currentHeight;
	int currentWidth;

};