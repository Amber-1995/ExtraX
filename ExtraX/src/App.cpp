#include "XX.h"
#include "GameWindow.h"
#include "Game.h"




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	XX::GameWindow game_window("Extra X", 1280, 720, WndProc);

	XX::ExtraX::graphics.Init(game_window.window, game_window.width, game_window.height);

	XX::ExtraX::input.Init(game_window.window);

	XX::Game game;

	int ret = game.Run();

	return ret;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

	XX::ExtraX::input.ProcessMessage(uMsg, wParam, lParam);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}