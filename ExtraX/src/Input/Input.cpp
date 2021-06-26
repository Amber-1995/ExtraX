/*==============================================================================

   [Input.cpp]
														 Author : Chen JianTong
														 Date   : 2020/11/01
-------------------------------------------------------------------------------

==============================================================================*/

#include "Input.h"

namespace XX
{
	Input::Input():
		_keyboard(),
		_mouse()
	{

	}

	void Input::Init(HWND window)
	{
		_keyboard.Init();
		_mouse.Init(window);
	}

	void Input::Update(void)
	{
		_keyboard.Update();
		_mouse.Update();
	}


	bool Input::GetKey(Keyboard_Keys key)
	{
		return _keyboard.GetKey(key);
	}

	bool Input::GetKeyUp(Keyboard_Keys key) 
	{
		return _keyboard.GetKeyUp(key);
	}

	bool Input::GetKeyDown(Keyboard_Keys key)
	{
		return _keyboard.GetKeyDown(key);
	}

	bool Input::GetButton(Mouse_Button button)
	{
		return _mouse.GetMouseButton(button);
	}

	bool Input::GetButtonUp(Mouse_Button button)
	{
		return _mouse.GetMouseButtonUp(button);
	}

	bool Input::GetButtonDown(Mouse_Button button)
	{
		return _mouse.GetMouseButtonDown(button);
	}

	XXVector2 Input::GetMousePosition(void)
	{
		return _mouse.GetMousePosition();
	}

	int Input::GetScrollWheelValue(void)
	{
		return _mouse.GetScrollWheelValue();
	}

	void Input::ResetScrollWheelValue(void)
	{
		_mouse.ResetScrollWheelValue();
	}

	void Input::SetMouseMode(Mouse_PositionMode mode)
	{
		_mouse.SetMode(mode);
	}

	void Input::SetMouseVisible(bool visible)
	{
		_mouse.SetVisible(visible);
	}

	bool Input::IsMouseConnected(void)
	{
		return _mouse.IsConnected();
	}

	bool Input::IsMouseVisible(void)
	{
		return _mouse.IsVisible();
	}

	void Input::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		_keyboard.ProcessMessage(message, wParam, lParam);
		_mouse.ProcessMessage(message, wParam, lParam);
	}
}