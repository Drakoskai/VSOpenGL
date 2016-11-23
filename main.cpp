#include <stdio.h>
#include <stdlib.h>
#include "GLWindow.h"
#include "GLDrawContext.h"
#include "Input.h"
#include <iostream>
#include "Model.h"


bool isRunning = true;

int main(int, char **)
{
	Input input = Input();
	GLDrawContext dc = GLDrawContext();
	dc.Init();

	MSG msg = { nullptr };

	Model model = Model("Assets/Meshes/cube.obj");
	model.Init(dc);

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
			if (input.IsKeyDown(Input::Escape))
			{
				isRunning = false;
			}

			dc.BeginScene();
			model.Draw(dc);


			dc.EndScene();
		}
	}

	model.Release();

	return 0;
}
