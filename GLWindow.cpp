#include "GLWindow.h"
#include "WinMain.h"
#include "Resource.h"

GLWindow::GLWindow()
	: m_hInst(WinMainParameters::GetHInstance()),
	m_prevInst(WinMainParameters::GetHPrevInstance()),
	m_lpCmdLine(WinMainParameters::GetLPCmdLine()),
	m_nCmdShow(WinMainParameters::GetNCmdShow()),
	m_hWnd(nullptr) { }

GLWindow::~GLWindow()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}

	UnregisterClass(m_title, m_hInst);
}

HWND GLWindow::Create(const DisplayState &displayState)
{
	GLRegisterClass();
	InitInstance(displayState);
	return m_hWnd;
}

HWND GLWindow::GetWindowHandle() const
{
	return m_hWnd;
}

LRESULT GLWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE){
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<long>((LPCREATESTRUCT(lParam))->lpCreateParams));
	}

	GLWindow* pView = GetViewFromObject(hWnd);
	if (pView)
	{
		pView->WinMsgHandler(hWnd, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT GLWindow::WinMsgHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(NULL);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

BOOL GLWindow::InitInstance(const DisplayState &displayState)
{
	int w = displayState.ScreenWidth;
	int h = displayState.ScreenHeight;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

	m_hWnd = CreateWindow(L"OpenGL", L"OpenGL",
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY,
		w, h,
		NULL, NULL, m_hInst, NULL);

	if (!m_hWnd)
	{
		MessageBox(m_hWnd, L"Could not create window object.", L"Error", MB_OK);
		return FALSE;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	SetFocus(m_hWnd);

	return TRUE;
}

ATOM GLWindow::GLRegisterClass() const
{
	WNDCLASSEX wcex = { };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_LAUNCHWIN32WINDOWFROMCONSOLE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"OpenGL";
	wcex.hIconSm = nullptr;

	return RegisterClassEx(&wcex);
}

