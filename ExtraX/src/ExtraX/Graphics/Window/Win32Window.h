#pragma once
#ifdef _WIN32 
#ifndef EXTRAX_WIN32_WINDOW_H
#define EXTRAX_WIN32_WINDOW_H

#include <ExtraX/Graphics/Window/WindowBase.h>


namespace ExtraX::Graphics::Base
{

	template<GRAPHICS_API GraphicsAPI>
	class Window<PLATFORM::Windows, GraphicsAPI> : public WindowBase
	{
	public:
		struct Descriptor
		{
			DWORD     exstyle;
			LPCSTR    class_name;
			LPCSTR    window_name;
			DWORD     style;
			int       x;
			int       y;
			int       width;
			int       height;
			HWND      parent;
			HMENU     menu;
			HINSTANCE instance;
			LPVOID    param;
		};

	private:
		HWND _hwnd;

		HINSTANCE _instance;

		std::string _class_name;

	public:
		Window(WNDCLASSEXA wcex, Descriptor descriptor)
		{
			_instance = wcex.hInstance;
			_class_name = wcex.lpszClassName;
#ifdef UNICODE
			std::string menu_name;
			std::wstring menu_name_w;
			std::string class_name;
			std::wstring class_name_w;
			std::string window_name;
			std::wstring window_name_w;

			WNDCLASSEXW wcex_w;
			ZeroMemory(&wcex_w, sizeof(WNDCLASSEXW));
			wcex_w.cbSize = sizeof(WNDCLASSEXW);
			wcex_w.style = wcex.style;
			wcex_w.lpfnWndProc = wcex.lpfnWndProc;
			wcex_w.cbClsExtra = wcex.cbClsExtra;
			wcex_w.cbWndExtra = wcex.cbWndExtra;
			wcex_w.hInstance = wcex.hInstance;
			wcex_w.hIcon = wcex.hIcon;
			wcex_w.hCursor = wcex.hCursor;
			wcex_w.hbrBackground = wcex.hbrBackground;

			if (wcex.lpszMenuName)
			{
				menu_name = wcex.lpszMenuName;
				menu_name_w = std::wstring(menu_name.begin(), menu_name.end());
				wcex_w.lpszMenuName = menu_name_w.c_str();
			}
			else
			{
				wcex_w.lpszMenuName = NULL;
			}

			if (wcex.lpszClassName)
			{
				class_name = wcex.lpszClassName;
				class_name_w = std::wstring(class_name.begin(), class_name.end());
				wcex_w.lpszClassName = class_name_w.c_str();
			}
			else
			{
				wcex_w.lpszClassName = NULL;
			}

			wcex_w.hIconSm = wcex.hIconSm;
			RegisterClassExW(&wcex_w);

			class_name = descriptor.class_name;
			class_name_w = std::wstring(class_name.begin(), class_name.end());
			window_name = descriptor.window_name;
			window_name_w = std::wstring(window_name.begin(), window_name.end());

			_hwnd = CreateWindowExW
			(
				descriptor.exstyle,
				class_name_w.c_str(),
				window_name_w.c_str(),
				descriptor.style,
				descriptor.x,
				descriptor.y,
				descriptor.width,
				descriptor.height,
				descriptor.parent,
				descriptor.menu,
				descriptor.instance,
				descriptor.param
			);
#else
			RegisterClassExA(&wcex);

			_hwnd = CreateWindowExA
			(
				descriptor.exstyle,
				descriptor.class_name,
				descriptor.window_name,
				descriptor.style,
				descriptor.x,
				descriptor.y,
				descriptor.width,
				descriptor.height,
				descriptor.parent,
				descriptor.menu,
				descriptor.instance,
				descriptor.param
			);

#endif // UNICODE
			ShowWindow(_hwnd, SW_SHOW);
			UpdateWindow(_hwnd);
		}

		Window()
		{
			_class_name = "ExtraX_Window_Class_Name";

			std::wstring class_name_w(_class_name.begin(), _class_name.end());

			auto window_process = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				switch (uMsg)
				{
				case WM_CLOSE:
					PostQuitMessage(0);
					DestroyWindow(hWnd);
					break;
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
				case WM_IME_KEYDOWN:
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_XBUTTONDOWN:
					Input::SetKeyState(wParam, KeyState::Down);
					break;
				case WM_KEYUP:
				case WM_SYSKEYUP:
				case WM_IME_KEYUP:
					Input::SetKeyState(wParam, KeyState::Up);
					break;
				case WM_LBUTTONUP:
					Input::SetKeyState(KeyCode::LeftMouseButton, KeyState::Up);
					break;
				case WM_RBUTTONUP:
					Input::SetKeyState(KeyCode::RightMouseButton, KeyState::Up);
					break;
				case WM_MBUTTONUP:
					Input::SetKeyState(KeyCode::MiddleMouseButton, KeyState::Up);
					break;
				case WM_XBUTTONUP:
					switch (GET_XBUTTON_WPARAM(wParam))
					{
					case XBUTTON1:
						Input::SetKeyState(KeyCode::X1MouseButton, KeyState::Up);
						break;

					case XBUTTON2:
						Input::SetKeyState(KeyCode::X2MouseButton, KeyState::Up);
						break;
					}
					break;

				case WM_MOUSEWHEEL:
					Input::SetScroolWheel(GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 1 : -1);
					break;
				case WM_MOUSEMOVE:
					Input::SetMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				}

				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			};
#ifdef UNICODE
			WNDCLASSEXW wcex_w;
			ZeroMemory(& wcex_w, sizeof(WNDCLASSEXW));
			wcex_w.cbSize = sizeof(WNDCLASSEXW);
			wcex_w.style = CS_CLASSDC | CS_OWNDC;
			wcex_w.lpfnWndProc = window_process;
			wcex_w.cbClsExtra = 0;
			wcex_w.cbWndExtra = 0;
			wcex_w.hInstance = GetModuleHandle(NULL);
			wcex_w.hIcon = NULL;
			wcex_w.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex_w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex_w.lpszMenuName = NULL;
			wcex_w.lpszClassName = class_name_w.c_str();
			wcex_w.hIconSm = NULL;
			RegisterClassExW(&wcex_w);
			_instance = wcex_w.hInstance;

			_hwnd = CreateWindowExW
			(
				0,
				class_name_w.c_str(),
				L"ExtraX",
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
				(GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2,
				(GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2,
				WINDOW_WIDTH,
				WINDOW_HEIGHT,
				NULL,
				NULL,
				GetModuleHandle(NULL),
				NULL
			);
#else

			WNDCLASSEXA wcex;
			ZeroMemory(&wcex, sizeof(WNDCLASSEXA));
			wcex.cbSize = sizeof(WNDCLASSEXA);
			wcex.style = CS_CLASSDC | CS_OWNDC;
			wcex.lpfnWndProc = window_process;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = GetModuleHandle(NULL);
			wcex.hIcon = NULL;
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = _class_name.c_str();
			wcex.hIconSm = NULL;
			RegisterClassExA(&wcex);
			_instance = wcex.hInstance;

			RegisterClassExA(&wcex);

			_hwnd = CreateWindowExA
			(
				0,
				_class_name.c_str(),
				"ExtraX",
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
				(GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2,
				(GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2,
				WINDOW_WIDTH,
				WINDOW_HEIGHT,
				NULL,
				NULL,
				GetModuleHandle(NULL),
				NULL
			);


#endif // UNICODE

			ShowWindow(_hwnd, SW_SHOW);
			UpdateWindow(_hwnd);
		}

		virtual ~Window()
		{
#ifdef UNICODE
			std::wstring class_name_w(_class_name.begin(), _class_name.end());
			UnregisterClassW(class_name_w.c_str(), _instance);
#else
			UnregisterClassA(_class_name.c_str(), _instance);
#endif // UNICODE
			DestroyWindow(_hwnd);
		}

		HWND GetHandle()
		{
			return _hwnd;
		}

		bool ShouldClose() override
		{
			MSG msg{};
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					return true;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return false;
		}

		int GetWidth() override
		{
			RECT rect;
			GetWindowRect(_hwnd, &rect);
			return rect.right - rect.left;	
		}

		int GetHeight() override
		{
			RECT rect;
			GetWindowRect(_hwnd, &rect);
			return rect.bottom - rect.top;
		}

		int GetPositionX() override
		{
			RECT rect;
			GetWindowRect(_hwnd, &rect);
			return rect.left;
		}

		int GetPositionY() override
		{
			RECT rect;
			GetWindowRect(_hwnd, &rect);
			return rect.top;
		}

		void SetTitle(const char* title) override
		{
#ifdef UNICODE
			std::string title_str = title;
			std::wstring title_wstr(title_str.begin(), title_str.end());
			SetWindowTextW(_hwnd, title_wstr.c_str());
#else
			SetWindowTextA(_hwnd, title);

#endif // UNICODE

		}

		void SetSize(int width, int length) override
		{
			MoveWindow
			(
				_hwnd,
				(GetSystemMetrics(SM_CXSCREEN) - width) / 2,
				(GetSystemMetrics(SM_CYSCREEN) - length) / 2,
				width,
				length,
				TRUE
			);
		}

		void SetPosition(int x, int y) override
		{
			RECT rect;
			GetWindowRect(_hwnd, &rect);
			MoveWindow
			(
				_hwnd,
				x,
				y,
				rect.right - rect.left,
				rect.bottom - rect.top,
				TRUE
			);
		}

	};

}


#endif // !EXTRAX_WIN32_WINDOW_H
#endif // _WIN32 
