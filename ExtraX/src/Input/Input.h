/*==============================================================================

   [Input.h]
														 Author : Chen JianTong
														 Date   : 2020/11/01
-------------------------------------------------------------------------------

==============================================================================*/


#ifndef __INPUT_H__
#define __INPUT_H__

#include "Keyboard.h"
#include "Mouse.h"
#include "../Data/Data.h"

namespace XX
{
	class Input
	{
	public:
		void Init(HWND window);

		void Update();
	
		bool GetKey(Keyboard_Keys key);
		bool GetKeyUp(Keyboard_Keys key);
		bool GetKeyDown(Keyboard_Keys key);

		bool GetButton(Mouse_Button button);
		bool GetButtonUp(Mouse_Button button);
		bool GetButtonDown(Mouse_Button button);
		XXVector2 GetMousePosition();
		int GetScrollWheelValue();

		void ResetScrollWheelValue();
		void SetMouseMode(Mouse_PositionMode mode);
		void SetMouseVisible(bool visible);

		bool IsMouseConnected();
		bool IsMouseVisible();

		void ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

	private:
		Keyboard _keyboard;
		Mouse _mouse;

		Input();
		Input(const Input& other) = delete;
		Input& operator=(const Input&) = delete;

		friend class ExtraX;
	};
}

#endif // !__INPUT_H__
