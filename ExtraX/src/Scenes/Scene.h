#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Data/ExtraXType.h"
#include <vector>

namespace XX
{
	class Scene
	{
	public:
		std::vector<GameObject*> const& game_objects;

		Scene();

		Scene(const Scene&) = delete;

		Scene& operator=(const Scene&) = delete;

		virtual ~Scene();

		void AddGameObject(GameObject* game_obeject);

		void RemoveGameObject(GameObject* game_obeject);

	private:
		std::vector<GameObject*> _game_objects;

	};
}


#endif // !_SCENE_H_
