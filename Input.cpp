#include "Input.h"
#include <stdint.h>

Input::Input() { m_keyState = { }; }

Input::~Input() { }

void Input::TranslateKeyMessage(MSG& msg, WPARAM wParam, LPARAM lParam)
{
	bool down = false;
	switch (msg.message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		down = true;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		break;
	default:
		return;
	}

	int vk = static_cast<int>(wParam);
	switch (vk)
	{
	case VK_SHIFT:
		vk = MapVirtualKey((lParam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
		if (!down)
		{
			KeyUp(VK_LSHIFT, m_keyState);
			KeyUp(VK_RSHIFT, m_keyState);
		}
		break;

	case VK_CONTROL:
		vk = (lParam & 0x01000000) ? VK_RCONTROL : VK_LCONTROL;
		break;

	case VK_MENU:
		vk = (lParam & 0x01000000) ? VK_RMENU : VK_LMENU;
		break;
	default: break;
	}

	if (down)
	{
		KeyDown(vk, m_keyState);
	}
	else
	{
		KeyUp(vk, m_keyState);
	}
}

void Input::KeyDown(int key, State& state)
{
	if (key < 0 || key > 0xfe)
		return;

	auto ptr = reinterpret_cast<uint32_t*>(&state);

	unsigned int bf = 1u << (key & 0x1f);
	ptr[(key >> 5)] |= bf;
}

Input::State Input::GetState() const
{
	return m_keyState;
}

void Input::KeyUp(int key, State& state)
{
	if (key < 0 || key > 0xfe)
	{
		return;
	}

	auto ptr = reinterpret_cast<uint32_t*>(&state);

	unsigned int bf = 1u << (key & 0x1f);
	ptr[(key >> 5)] &= ~bf;
}

bool Input::IsKeyDown(Keys key) const
{
	if (key >= 0 && key <= 0xff)
	{
		auto ptr = reinterpret_cast<const uint32_t*>(this);
		unsigned int bf = 1u << (key & 0x1f);
		return (ptr[(key >> 5)] & bf) != 0;
	}

	return false;
}

bool Input::IsKeyUp(Keys key) const
{
	if (key >= 0 && key <= 0xfe)
	{
		auto ptr = reinterpret_cast<const uint32_t*>(this);
		unsigned int bf = 1u << (key & 0x1f);
		return (ptr[(key >> 5)] & bf) == 0;
	}

	return false;
}
