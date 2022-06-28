#ifndef CORE_MODULE_H
#define CORE_MODULE_H


#include "Common/ExtraX.h"



namespace XX::Game
{
	class Scene;
	class GameObject;
	class Component;

	class Scene
	{
		friend class GameObject;
		friend class Component;

	private:
		std::list<GameObject*> _new_game_objects;

		std::list<GameObject*> _current_game_objects;

		std::list<GameObject*> _deleted_game_objects;

		static void _SubProcess(size_t thread);

		//inline static ThreadManager _thread_manager = { _SubProcess , THREAD_NUM };

	public:
		Scene();
		
		virtual ~Scene();

		void FramePreprocess();

		void FrameProcess();

		template<class T, class... ARGS> 
		T* AddGameObject(ARGS... args);
	};

	class GameObject
	{
		friend class Scene;
		friend class Component;

 	private:
		inline static Scene* _current_scene;

		std::list<Component*> _new_components;

		std::list<Component*> _current_components;

		std::list<Component*> _deleted_components;

		std::list<GameObject*>::iterator _self;

		static void _SetCurrentScene(Scene* scene);

		void _FramePreprocess();

	public:
		Scene* const scene = _current_scene;

		GameObject();
	
		virtual ~GameObject();

		void Destroy();

		template<class T, class... ARGS>
		T* AddComponent(ARGS... args);
		
	};

	class Component
	{
		friend class Scene;
		friend class GameObject;

	private:
		inline static Scene* _current_scene;

		inline static GameObject* _current_game_object;

		std::list<Component*>::iterator _self;

		inline static void _SetCurrentSceneAndGameObject(Scene* scene, GameObject* game_object);

	public:
		Scene* const scene = _current_scene;

		GameObject* const game_object = _current_game_object;

		Component();

		virtual ~Component() {}

		std::list<Component*>& GetComponents();

		template<class T>
		T* GetComponent();

		void Destroy();
	};

	template<class T>
	inline T* Component::GetComponent()
	{
		for (auto& i : game_object->_current_components)
		{
			T* t = dynamic_cast<T*>(i);
			if (t)
			{
				return t;
			}
		}
		return nullptr;
	}

	template<class T, class... ARGS>
	inline T* Scene::AddGameObject(ARGS... args)
	{
		GameObject::_SetCurrentScene(this);

		return new T(args...);
	}

	template<class T, class ...ARGS>
	inline T* GameObject::AddComponent(ARGS ...args)
	{
		Component::_SetCurrentSceneAndGameObject(scene, this);
		return new T(args...);
	}

}



#endif // !CORE_MODULE_H
