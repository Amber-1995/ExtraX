#include "keyboard.h"
#include <assert.h>

namespace XX 
{

	Keyboard::Keyboard(void) :
		_current_state(),
		_last_state()
	{

	}

	void Keyboard::Init()
	{
		ZeroMemory(&_current_state, sizeof(Keyboard_State));
		ZeroMemory(&_last_state, sizeof(Keyboard_State));
	}

	void Keyboard::Update(void)
	{
		_last_state = _current_state;
	}

	void Keyboard::Reset(void)
	{
		ZeroMemory(&_current_state, sizeof(Keyboard_State));
		ZeroMemory(&_last_state, sizeof(Keyboard_State));
	}


	bool Keyboard::GetKey(Keyboard_Keys key)
	{
		if (key <= 0xfe)
		{
			unsigned int* p = (unsigned int*)&_current_state;
			unsigned int bf = 1u << (key & 0x1f);
			return (p[(key >> 5)] & bf) != 0;
		}
		return false;
	}

	bool Keyboard::GetKeyDown(Keyboard_Keys key)
	{
		if (key <= 0xfe)
		{
			unsigned int* l_p = (unsigned int*)&_last_state;
			unsigned int l_bf = 1u << (key & 0x1f);
			bool last = (l_p[(key >> 5)] & l_bf) != 0;

			unsigned int* c_p = (unsigned int*)&_current_state;
			unsigned int c_bf = 1u << (key & 0x1f);
			bool current = (c_p[(key >> 5)] & c_bf) != 0;

			return ((!last) && current);
		}
		return false;
	}

	bool Keyboard::GetKeyUp(Keyboard_Keys key)
	{
		if (key <= 0xfe)
		{
			unsigned int* l_p = (unsigned int*)&_last_state;
			unsigned int l_bf = 1u << (key & 0x1f);
			bool last = (l_p[(key >> 5)] & l_bf) != 0;

			unsigned int* c_p = (unsigned int*)&_current_state;
			unsigned int c_bf = 1u << (key & 0x1f);
			bool current = (c_p[(key >> 5)] & c_bf) != 0;

			return (last && (!current));
		}
		return false;
	}

	void  Keyboard::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{

		bool down = false;

		switch (message)
		{
		case WM_ACTIVATEAPP:
			Reset();
			return;

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

		int vk = (int)wParam;
		switch (vk)
		{
		case VK_SHIFT:
			vk = (int)MapVirtualKey(((unsigned int)lParam & 0x00ff0000) >> 16u, MAPVK_VSC_TO_VK_EX);
			if (!down)
			{
				// 左シフトと右シフトの両方が同時に押された場合にクリアされるようにするための回避策
				keyUp(VK_LSHIFT);
				keyUp(VK_RSHIFT);
			}
			break;

		case VK_CONTROL:
			vk = ((UINT)lParam & 0x01000000) ? VK_RCONTROL : VK_LCONTROL;
			break;

		case VK_MENU:
			vk = ((UINT)lParam & 0x01000000) ? VK_RMENU : VK_LMENU;
			break;
		}

		if (down)
		{
			keyDown(vk);
		}
		else
		{
			keyUp(vk);
		}
	}

	void Keyboard::keyUp(int key)
	{
		if (key < 0 || key > 0xfe) { return; }

		unsigned int* p = (unsigned int*)&_current_state;
		unsigned int bf = 1u << (key & 0x1f);
		p[(key >> 5)] &= ~bf;
	}

	void Keyboard::keyDown(int key)
	{
		if (key < 0 || key > 0xfe) { return; }

		unsigned int* p = (unsigned int*)&_current_state;
		unsigned int bf = 1u << (key & 0x1f);
		p[(key >> 5)] |= bf;
	}

}