#pragma once
#ifndef _GAME_H_
#define _GAME_H_


namespace XX
{
	class Game
	{
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		virtual ~Game();

		int Run();

	};
}

#endif /!_GAME_H_