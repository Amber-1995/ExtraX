#pragma once
#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_
#include <Windows.h>
#include <string>

namespace XX
{
	typedef LRESULT(CALLBACK* WndProc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class GameWindow
	{
	public:
		const HWND& window;
		const int& width;
		const int& height;

		GameWindow(const std::string& window_name, int width, int height, WndProc wnd_proc = _WndProc);
		GameWindow(const GameWindow&) = delete;
		GameWindow& operator=(const GameWindow&) = delete;
		virtual ~GameWindow();

	private:
		HWND _window;
		int _width;
		int _height;

		static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}


#endif // !_GAME_WINDOW_H_
