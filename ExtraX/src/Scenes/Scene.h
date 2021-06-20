#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Data/Data.h"
#include <list>

namespace XX
{
	class Scene
	{
	public:
		std::list<GameObjectPtr> const& game_objects;

		Scene();

		Scene(const Scene&) = delete;

		Scene& operator=(const Scene&) = delete;

		virtual ~Scene();

		void Awake();

		void Destroy();

		void AddGameObject(GameObjectPtr game_obeject);

		void RemoveGameObject(GameObject* game_obeject);

		template<class T = Scene, class ...ARGS>
		static ScenePtr Create(ARGS ...args);

	private:
		std::list<GameObjectPtr> _game_objects;

		bool _is_awake;

		//ScenePtr _Get();

	};

	template<class T, class ...ARGS>
	inline ScenePtr Scene::Create(ARGS ...args)
	{
		return ScenePtr(new T(args...));
	}
}


#endif // !_SCENE_H_
