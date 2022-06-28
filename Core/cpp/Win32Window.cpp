#ifdef WINDOWS

#include "Common/Window.h"
#include <Windows.h>


std::unordered_map<XX::Window*, HWND> win_hwnd;


HWND GetWindowsHWND(XX::Window* window)
{
	return win_hwnd[window];
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		XX::ExtraX::Exit();
		PostQuitMessage(0);
		break;
	}

	case WM_SIZE:
	{
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

namespace XX
{
	Window::Window(int width, int height, const std::string& title):
		_width(width),
		_height(height),
		_title(title)
	{
		std::string class_name = std::to_string((size_t)this);

		WNDCLASSEX wnd_class =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WndProc,
			0,
			0,
			GetModuleHandle(NULL),
			NULL,
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			NULL,
			class_name.c_str(),
			NULL
		};

		RegisterClassEx(&wnd_class);
		HWND hwnd = CreateWindowEx(
			0,
			class_name.c_str(),
			title.c_str(),
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			(width + GetSystemMetrics(SM_CXDLGFRAME) * 2),
			(height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);

		win_hwnd[this] = hwnd;

		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
	}

	Window::~Window()
	{
		std::string class_name = std::to_string((size_t)this);
		UnregisterClass(class_name.c_str(), GetModuleHandle(NULL));
		DestroyWindow(win_hwnd[this]);
		win_hwnd.erase(win_hwnd.find(this));
	}

	uint32_t Window::GetWidth()
	{
		return _width;
	}

	uint32_t Window::GetHeight()
	{
		return _height;
	}

	void Window::SetSize(uint32_t width, uint32_t height)
	{
		_width = width;
		_height = height;
		MoveWindow(win_hwnd[this], 200, 200, width, height, TRUE);
	}

	std::string Window::GetTitle()
	{
		return _title;
	}

	void Window::SetTitle(const std::string& title)
	{

	}

	void Window::SetFullScreen(bool enalbe)
	{

	}
}










#endif // WINDOWS
