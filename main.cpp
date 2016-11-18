#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GLWindow.h"
#include "GLInput.h"
#include "GLDeviceResources.h"
#include "GLDrawContext.h"

bool isRunning = true;
const bool FullScreen = false;
const bool VsynEnabled = true;
const float ScreenDepth = 1000.0f;
const float ScreenNear = 0.1f;

int main(int, char **)
{
	GLWindow * window = new GLWindow();
	window->Create();
	GLInput input = GLInput();
	GLDeviceResources* gl = new GLDeviceResources();
	gl->Init(window->GetWindowHandle());
	gl->InitOpenGL(window->GetWindowHandle(), 1280, 720, ScreenDepth, ScreenNear, VsynEnabled);
	
	GLDrawContext * dc = new GLDrawContext(gl);
	dc->Init();
	MSG msg = { nullptr };
	while (isRunning)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			isRunning = false;
		}
		else
		{
			input.TranslateKeyMessage(msg, msg.wParam, msg.lParam);
			if (input.IsKeyDown(GLInput::Escape))
			{
				isRunning = false;
			}
			dc->BeginScene();
			dc->EndScene();
		}
	}
	delete dc;

	gl->Release(window->GetWindowHandle());

	delete gl;

	delete window;

	return 0;
}
