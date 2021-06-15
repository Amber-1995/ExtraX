#include "XX.h"
#include "GameWindow.h"
#include "Game.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	XX::GameWindow game_window("Extra X",960 , 540);

	XX::ExtraX::graphics.Init(game_window.window, game_window.width, game_window.height);

	XX::Game game;

	int ret = game.Run();

	return ret;
}