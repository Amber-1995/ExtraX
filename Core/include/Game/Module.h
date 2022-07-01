#ifndef CORE_MODULE_H
#define CORE_MODULE_H


#include "Common/ExtraX.h"



namespace XX::Game
{
	class Scene;
	class GameObject;
	class Component;

	namespace Event
	{
		class IUpdate;
		class IRender2D;
		class IRender3D;
	}

	XXAPI class Scene
	{
		friend class GameObject;
		friend class Component;

	private:
		class GameObjectsManager
		{
		public:
			Scene* const scene;

			inline static  std::mutex mutex;

			std::list<GameObject*> new_game_objects;

			std::list<GameObject*> current_game_objects;

			std::list<GameObject*> deleted_game_objects;

			GameObjectsManager(Scene* scene);

			virtual ~GameObjectsManager();

			void Lock();

			void Unlock();

			void Add(GameObject* game_object);

			void Remove(GameObject* game_object);

			void Update();

		} _game_objects_manager = { this };

		class UpdateManager
		{
		public:
			std::list<Event::IUpdate*> update_list;
			void Add(Component* component);
			void Remove(Component* component);
			void ProcessPerThread(size_t thread_num);
		} _update_manager;

		class Render2DManager
		{
		public:
			std::list<Event::IRender2D*> render2d_list;
			void Add(Component* component);
			void Remove(Component* component);
			void ProcessPerThread(size_t thread_num);
		} _render2d_manager;
		
		class Render3DManager
		{
		public:
			std::list<Event::IRender3D*> update_list;
			void Add(Component* component);
			void Remove(Component* component);
			void ProcessPerThread();
		} _render3d_manager;
		inline static Scene* _focus_scene = nullptr;

		void _ProcessPerThread(size_t thread);

		void _Preprocess();

		void _Process();

		ThreadManager _thread_manager = { THREAD_NUM };

	public:
		void Start();

		void Run();

		template<class T, class... ARGS> 
		T* AddGameObject(ARGS... args);
	};

	class GameObject
	{
		friend class Scene;
		friend class Component;

 	private:
		class ComponentsManager
		{
			friend class Component;
		private:
			Scene* const _scene;

			GameObject* const _game_object;

			inline static std::mutex _mutex;

			std::list<Component*> _new_components;

			std::list<Component*> _new_components_copy;

			std::list<Component*> _current_components;

			std::list<Component*> _deleted_components;

		public:
			ComponentsManager(Scene* scene, GameObject* game_object);

			virtual ~ComponentsManager();

			void Lock();

			void Unlock();

			void Add(Component* component);

			void Remove(Component* component);

			void Update();

		} _components_manager = { Scene::_focus_scene, this };

		inline static Scene* _focus_scene = nullptr;

		inline static GameObject* _focus_game_object = nullptr;

		std::list<GameObject*>::iterator _self;

		void _FramePreprocess();

	public:
		Scene* const scene = Scene::_focus_scene;

		void Destroy();

		template<class T, class... ARGS>
		T* AddComponent(ARGS... args);
		
	};

	class Component
	{
		friend class Scene;
		friend class GameObject;

	private:
		std::list<Component*>::iterator _self;

	public:
		Scene* const scene = GameObject::_focus_scene;

		GameObject* const game_object = GameObject::_focus_game_object;

		virtual ~Component() {}

		std::list<Component*>& GetComponents();

		template<class T>
		T* GetComponent();

		void Destroy();
	};

	template<class T>
	inline T* Component::GetComponent()
	{
		for (auto& i : game_object->_components_manager._current_components)
		{
			T* t = dynamic_cast<T*>(i);
			if (t) return t;
		}
		return nullptr;
	}

	template<class T, class... ARGS>
	inline T* Scene::AddGameObject(ARGS... args)
	{
		_game_objects_manager.Lock();
		T* t = new T(args...);
		_game_objects_manager.Add(t);
		_game_objects_manager.Unlock();
		return t;
	}

	template<class T, class ...ARGS>
	inline T* GameObject::AddComponent(ARGS ...args)
	{
		_components_manager.Lock();
		T* t = new T(args...);
		_components_manager.Add(t);
		_components_manager.Unlock();
		return t;
	}

}



#endif // !CORE_MODULE_H
