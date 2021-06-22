#include "GameWindow.h"

XX::GameWindow::GameWindow(const std::string& window_name, int width, int height, WndProc wnd_proc):
	window(_window),
	width(_width),
	height(_height),
	_width(width),
	_height(height)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		wnd_proc,
		0,
		0,
		GetModuleHandle(NULL),
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"game window",
		NULL
	};

	RegisterClassEx(&wcex);

	_window = CreateWindowEx(
		0,
		"game window",
		window_name.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(width + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);


	ShowWindow(_window, SW_SHOW);
	UpdateWindow(_window);
}

XX::GameWindow::~GameWindow()
{
	DestroyWindow(window);
}

LRESULT XX::GameWindow::_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: 
	{
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
