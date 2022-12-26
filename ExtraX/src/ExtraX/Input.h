#pragma once
#ifndef EXTRAX_INPUT_H
#define EXTRAX_INPUT_H

#include <ExtraX/Common.h>

namespace ExtraX
{
	struct KeyCode
	{
		KeyCode() = delete;

		static constexpr size_t Unknown = 0x00;
		static constexpr size_t LeftMouseButton = 0x01;
		static constexpr size_t RightMouseButton = 0x02;
		static constexpr size_t ControlBreakProcessing = 0x03;
		static constexpr size_t MiddleMouseButton = 0x04;
		static constexpr size_t X1MouseButton = 0x05;
		static constexpr size_t X2MouseButton = 0x06;

		static constexpr size_t Backspace = 0x08;
		static constexpr size_t Tab = 0x09;

		static constexpr size_t Clear = 0x0c;
		static constexpr size_t Enter = 0x0d;

		static constexpr size_t Shift = 0x10;
		static constexpr size_t Ctrl = 0x11;
		static constexpr size_t Alt = 0x12;
		static constexpr size_t Pause = 0x13;
		static constexpr size_t CapsLock = 0x14;
		static constexpr size_t IMEKanaMode = 0x15;
		static constexpr size_t IMEHanguelMode = 0x15;
		static constexpr size_t IMEOn = 0x16;
		static constexpr size_t IMEJunjaMode = 0x17;
		static constexpr size_t IMEFinalMode = 0x18;
		static constexpr size_t IMEHanjaMode = 0x19;
		static constexpr size_t IMEKanjiMode = 0x19;
		static constexpr size_t IMEOff = 0x1a;
		static constexpr size_t Esc = 0x1b;
		static constexpr size_t IMEConvert = 0x1c;
		static constexpr size_t IMENonconvert = 0x1d;
		static constexpr size_t IMEAccept = 0x1e;
		static constexpr size_t IMEModeChangeRequst = 0x1f;
		static constexpr size_t Spacebar = 0x20;
		static constexpr size_t PageUp = 0x21;
		static constexpr size_t PageDown = 0x22;
		static constexpr size_t End = 0x23;
		static constexpr size_t Home = 0x24;
		static constexpr size_t LeftArrow = 0x25;
		static constexpr size_t UpArrow = 0x26;
		static constexpr size_t RightArrow = 0x27;
		static constexpr size_t DownArrow = 0x28;
		static constexpr size_t Select = 0x29;
		static constexpr size_t Print = 0x2a;
		static constexpr size_t Execute = 0x2b;
		static constexpr size_t PrintScreen = 0x2c;
		static constexpr size_t Insert = 0x2d;
		static constexpr size_t Delete = 0x2e;
		static constexpr size_t Help = 0x2f;
		static constexpr size_t Num0 = 0x30;
		static constexpr size_t Num1 = 0x31;
		static constexpr size_t Num2 = 0x32;
		static constexpr size_t Num3 = 0x33;
		static constexpr size_t Num4 = 0x34;
		static constexpr size_t Num5 = 0x35;
		static constexpr size_t Num6 = 0x36;
		static constexpr size_t Num7 = 0x37;
		static constexpr size_t Num8 = 0x38;
		static constexpr size_t Num9 = 0x39;

		static constexpr size_t A = 0x41;
		static constexpr size_t B = 0x42;
		static constexpr size_t C = 0x43;
		static constexpr size_t D = 0x44;
		static constexpr size_t E = 0x45;
		static constexpr size_t F = 0x46;
		static constexpr size_t G = 0x47;
		static constexpr size_t H = 0x48;
		static constexpr size_t I = 0x49;
		static constexpr size_t J = 0x4a;
		static constexpr size_t K = 0x4b;
		static constexpr size_t L = 0x4c;
		static constexpr size_t M = 0x4d;
		static constexpr size_t N = 0x4e;
		static constexpr size_t O = 0x4f;
		static constexpr size_t P = 0x50;
		static constexpr size_t Q = 0x51;
		static constexpr size_t R = 0x52;
		static constexpr size_t S = 0x53;
		static constexpr size_t T = 0x54;
		static constexpr size_t U = 0x55;
		static constexpr size_t V = 0x56;
		static constexpr size_t W = 0x57;
		static constexpr size_t X = 0x58;
		static constexpr size_t Y = 0x59;
		static constexpr size_t Z = 0x5a;
		static constexpr size_t LeftWindows = 0x5b;
		static constexpr size_t RightWindows = 0x5c;
		static constexpr size_t Applications = 0x5d;

		static constexpr size_t ComputerSleep = 0x5f;
		static constexpr size_t NumericKeypad0 = 0x60;
		static constexpr size_t NumericKeypad1 = 0x61;
		static constexpr size_t NumericKeypad2 = 0x62;
		static constexpr size_t NumericKeypad3 = 0x63;
		static constexpr size_t NumericKeypad4 = 0x64;
		static constexpr size_t NumericKeypad5 = 0x65;
		static constexpr size_t NumericKeypad6 = 0x66;
		static constexpr size_t NumericKeypad7 = 0x67;
		static constexpr size_t NumericKeypad8 = 0x68;
		static constexpr size_t NumericKeypad9 = 0x69;
		static constexpr size_t Multiply = 0x6a;
		static constexpr size_t Add = 0x6b;
		static constexpr size_t Separator = 0x6c;
		static constexpr size_t Subract = 0x6d;
		static constexpr size_t Decimal = 0x6e;
		static constexpr size_t Divide = 0x6f;
		static constexpr size_t F1 = 0x70;
		static constexpr size_t F2 = 0x71;
		static constexpr size_t F3 = 0x72;
		static constexpr size_t F4 = 0x73;
		static constexpr size_t F5 = 0x74;
		static constexpr size_t F6 = 0x75;
		static constexpr size_t F7 = 0x76;
		static constexpr size_t F8 = 0x77;
		static constexpr size_t F9 = 0x78;
		static constexpr size_t F10 = 0x79;
		static constexpr size_t F11 = 0x7a;
		static constexpr size_t F12 = 0x7b;
		static constexpr size_t F13 = 0x7c;
		static constexpr size_t F14 = 0x7d;
		static constexpr size_t F15 = 0x7e;
		static constexpr size_t F16 = 0x7f;
		static constexpr size_t F17 = 0x80;
		static constexpr size_t F18 = 0x81;
		static constexpr size_t F19 = 0x82;
		static constexpr size_t F20 = 0x83;
		static constexpr size_t F21 = 0x84;
		static constexpr size_t F22 = 0x85;
		static constexpr size_t F23 = 0x86;
		static constexpr size_t F24 = 0x87;
		static constexpr size_t F25 = 0x88;

		static constexpr size_t NumLock = 0x90;
		static constexpr size_t ScrollLock = 0x91;

		static constexpr size_t LetfShift = 0xa0;
		static constexpr size_t RightShift = 0xa1;
		static constexpr size_t LeftCtrl = 0xa2;
		static constexpr size_t RightCtrl = 0xa3;
		static constexpr size_t LeftAlt = 0xa4;
		static constexpr size_t RightAlt = 0xa5;
		static constexpr size_t BrowserBack = 0xa6;
		static constexpr size_t BrowserForward = 0xa7;
		static constexpr size_t BrowserRefresh = 0xa8;
		static constexpr size_t BrowserStop = 0xa9;
		static constexpr size_t BrowserSearch = 0xaa;
		static constexpr size_t BrowserFavorites = 0xab;
		static constexpr size_t BrowserStartAndHome = 0xac;
		static constexpr size_t VolumeMute = 0xad;
		static constexpr size_t VolumeDown = 0xae;
		static constexpr size_t VolumeUp = 0xaf;
		static constexpr size_t NextTrack = 0xb0;
		static constexpr size_t PreviousTrack = 0xb1;
		static constexpr size_t StopMedia = 0xb2;
		static constexpr size_t PlayOrPauseMedia = 0xb3;
		static constexpr size_t StartMail = 0xb4;
		static constexpr size_t SelectMedia = 0xb5;
		static constexpr size_t StartAppliction1 = 0xb6;
		static constexpr size_t StartAppliction2 = 0xb7;

		static constexpr size_t Semicolon = 0xba;
		static constexpr size_t OEM_1 = 0xba;
		static constexpr size_t PlusSign = 0xbb;
		static constexpr size_t Comma = 0xbc;
		static constexpr size_t MinusSign = 0xbd;
		static constexpr size_t Period = 0xbe;
		static constexpr size_t Slash_QuestionMark = 0xbf;
		static constexpr size_t OEM_2 = 0xbf;
		static constexpr size_t Tilde = 0xc0;
		static constexpr size_t OEM_3 = 0xc0;

		static constexpr size_t LeftBracket = 0xdb;
		static constexpr size_t OEM_4 = 0xdc;
		static constexpr size_t Backslash_VerticalBar = 0xdc;
		static constexpr size_t OEM_5 = 0xdb;
		static constexpr size_t RightBracket = 0xdd;
		static constexpr size_t OEM_6 = 0xdd;
		static constexpr size_t SingleQuote_DoubleQuote = 0xde;
		static constexpr size_t OEM_7 = 0xde;
		static constexpr size_t OEM_8 = 0xdf;

		static constexpr size_t OEM_102 = 0xe2;

		static constexpr size_t IMEProcess = 0xe5;

		static constexpr size_t Packet = 0xe7;

		static constexpr size_t Attn = 0xf6;
		static constexpr size_t CrSel = 0xf7;
		static constexpr size_t ExSel = 0xf8;
		static constexpr size_t EraseEOF = 0xf9;
		static constexpr size_t Play = 0xfa;
		static constexpr size_t Zoom = 0xfb;
		static constexpr size_t PA1 = 0xfd;
		static constexpr size_t OEM_Clear = 0xfe;
	};

	struct KeyState
	{
		KeyState() = delete;
		static constexpr bool Up = false;
		static constexpr bool Down = true;
	};

	class Input
	{
	private:
		inline static std::bitset<0xff> _key_states_current;

		inline static std::bitset<0xff> _key_states_latest;

		inline static int _scroll_wheel;

		inline static int _mouse_position_x;

		inline static int _mouse_position_y;

	public:
		Input() = delete;

		inline static bool GetKey(size_t keycode)
		{
			return _key_states_current[keycode];
		}

		inline static bool GetKeyDown(size_t keycode)
		{
			return ((!_key_states_latest[keycode]) && _key_states_current[keycode]);
		}

		inline static bool GetKeyUp(size_t keycode)
		{
			return (_key_states_latest[keycode] && (!_key_states_current[keycode]));
		}

		inline static int GetScroolWheel()
		{
			return _scroll_wheel;
		}

		inline static int GetMousePositionX()
		{
			return _mouse_position_x;
		}

		inline static int GetMousePositionY()
		{
			return _mouse_position_y;
		}

		inline static void Reset()
		{
			_key_states_current.reset();
			_key_states_latest.reset();
		}

		inline static void SetKeyState(size_t keycode, bool state)
		{
			_key_states_current[keycode] = state;
		}

		inline static void SetScroolWheel(int value)
		{
			_scroll_wheel += value;
		}

		inline static void SetMousePosition(int x, int y)
		{
			_mouse_position_x = x;
			_mouse_position_y = y;
		}

		inline static void Update()
		{
			_key_states_latest = _key_states_current;
			_scroll_wheel = 0;
		}
	};
}




#endif // !EXTRAX_INPUT_H
