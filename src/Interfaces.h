#pragma once

#include <windows.h>

namespace View
{
	static const int MaxLoadString = 100;
	static const int DefaultWidth = 1280;
	static const int DefaultHeight = 720;
	static const bool DefaultFullScreen = false;
	static const bool DefaultVsynEnabled = true;
	static const float DefaultScreenDepth = 100.0f;
	static const float DefaultScreenNear = 0.1f;
	static const float DefaultFieldOfView = 45.0f;
	static const float DefaultAspectRatio = static_cast<float>(DefaultWidth) / static_cast<float>(DefaultHeight);
}

struct DisplayState
{
	int ScreenHeight;
	int ScreenWidth;
	bool FullScreen;
	bool VsynEnabled;
	float ScreenDepth;
	float ScreenNear;
	DisplayState()
		: ScreenHeight(View::DefaultHeight),
		ScreenWidth(View::DefaultWidth),
		FullScreen(View::DefaultFullScreen),
		VsynEnabled(View::DefaultVsynEnabled),
		ScreenDepth(View::DefaultScreenDepth),
		ScreenNear(View::DefaultScreenNear) { }
};
