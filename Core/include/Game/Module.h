#ifndef CORE_MODULE_H
#define CORE_MODULE_H


#include "Common/ExtraX.h"
#include "Event.h"

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

		} *_game_objects_manager = new GameObjectsManager(this);

		class UpdateManager : public Event::EventManager<Event::IUpdate>
		{
		public:
			void ProcessPerThread(size_t thread_num);
		} *_update_manager = new UpdateManager;

		class Render3DManager : public Event::EventManager<Event::IRender3D>
		{
		public:
			void ProcessPerThread(size_t thread_num);
		} *_render3d_manager = new Render3DManager;
		
		class Render2DManager : public Event::EventManager<Event::IRender2D>
		{
		public:
			void ProcessPerThread(size_t thread_num);
		} *_render2d_manager = new Render2DManager;

		inline static Scene* _focus_scene = nullptr;

		void _ProcessPerThread(size_t thread_num);

		void _Preprocess();

		void _Process();

		ThreadManager _thread_manager = { ExtraX::thread_num };

	public:
		virtual ~Scene();

		void Start();

		void Run();

		template<class T, class... ARGS> 
		T* AddGameObject(ARGS... args);
	};

	XXAPI class GameObject
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

		} *_components_manager = new ComponentsManager(Scene::_focus_scene, this);

		class OnStartManager : public Event::EventManager<Event::IOnStart>
		{
		public:
			void OnStart();
		} *_onstart_manager = new OnStartManager;

		class OnTansformManager : public Event::EventManager<Event::IOnTransform>
		{
		public:
			void OnTansform();
		} *_ontransform_manager = new OnTansformManager;

		class OnTranslateManager : public Event::EventManager<Event::IOnTranslate>
		{
		public:
			void OnOnTranslate();
		} *_ontranslate_manager = new OnTranslateManager;

		class OnRotateManager : public Event::EventManager<Event::IOnRotate>
		{
		public:
			void  OnRotate();
		} *_onrotate_manager = new OnRotateManager;

		class OnScaleManager : public Event::EventManager<Event::IOnScale>
		{
		public:
			void OnOnScale();
		}*_onscale_manager = new OnScaleManager;

		inline static Scene* _focus_scene = nullptr;

		inline static GameObject* _focus_game_object = nullptr;

		std::list<GameObject*>::iterator _self;

		void _FramePreprocess();

	public:
		virtual ~GameObject();

		Scene* const scene = Scene::_focus_scene;

		void Destroy();

		template<class T, class... ARGS>
		T* AddComponent(ARGS... args);
		
	};

	XXAPI class Component
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
		for (auto& i : game_object->_components_manager->_current_components)
		{
			T* t = dynamic_cast<T*>(i);
			if (t) return t;
		}
		return nullptr;
	}

	template<class T, class... ARGS>
	inline T* Scene::AddGameObject(ARGS... args)
	{
		_game_objects_manager->Lock();
		T* t = new T(args...);
		_game_objects_manager->Add(t);
		_game_objects_manager->Unlock();
		return t;
	}

	template<class T, class ...ARGS>
	inline T* GameObject::AddComponent(ARGS ...args)
	{
		_components_manager->Lock();
		T* t = new T(args...);
		_components_manager->Add(t);
		_components_manager->Unlock();
		return t;
	}

}



#endif // !CORE_MODULE_H
