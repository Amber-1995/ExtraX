#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "Scenes/Scene.h"

namespace XX
{
	class Game
	{
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		virtual ~Game();

		int Run(HWND window);

		void NextScene(ScenePtr scene);

	private:
		ScenePtr _scene;
		ScenePtr _next_scene;
	};
}

#endif /!_GAME_H_