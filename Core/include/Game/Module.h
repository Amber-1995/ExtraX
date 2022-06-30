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
		inline static std::mutex _mutex;

		std::list<GameObject*> _new_game_objects;

		std::list<GameObject*> _new_game_objects_copy;

		std::list<GameObject*> _current_game_objects;

		std::list<GameObject*> _deleted_game_objects;

		static void _SubProcess(size_t thread);

		//inline static ThreadManager _thread_manager = { _SubProcess , THREAD_NUM };

	public:
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
		inline static std::mutex _mutex;

		inline static Scene* _current_scene;

		std::list<Component*> _new_components;

		std::list<Component*> _new_components_copy;

		std::list<Component*> _current_components;

		std::list<Component*> _deleted_components;

		std::list<GameObject*>::iterator _self;


		void _FramePreprocess();

	public:
		Scene* const scene = _current_scene;
	
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

	public:
		Scene* const scene = _current_scene;

		GameObject* const game_object = _current_game_object;

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
		_mutex.lock();
		GameObject::_current_scene = this;
		T* t = new T(args...);
		GameObject* new_game_object = t;
		_new_game_objects_copy.push_front(new_game_object);
		_new_game_objects.push_front(new_game_object);
		new_game_object->_self = _new_game_objects.begin();
		_mutex.unlock();
		return t;
	}

	template<class T, class ...ARGS>
	inline T* GameObject::AddComponent(ARGS ...args)
	{
		_mutex.lock();
		Component::_current_scene = scene;
		Component::_current_game_object = this;
		T* t = new T(args...);
		Component* new_component = t;
		_new_components_copy.push_front(new_component);
		_new_components.push_front(new_component);
		new_component->_self = _new_components.begin();
		_mutex.unlock();
		return t;
	}

}



#endif // !CORE_MODULE_H
