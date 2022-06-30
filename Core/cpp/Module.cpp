#include "Game/Module.h"
#include "Game/Event/Event.h"
#include "Common/Graphics.h"


namespace XX::Game
{
	Scene::GameObjectsManager::GameObjectsManager(Scene* scene):
		_scene(scene)
	{

	}

	Scene::GameObjectsManager::~GameObjectsManager()
	{
		for (auto& i : _new_game_objects)
		{
			delete i;
		}

		for (auto& i : _current_game_objects)
		{
			delete i;
		}
	}

	void Scene::GameObjectsManager::Lock()
	{
		_mutex.lock();
		Scene::_focus_scene = _scene;
	}

	void Scene::GameObjectsManager::Unlock()
	{
		_mutex.unlock();
	}

	void Scene::GameObjectsManager::Add(GameObject* game_object)
	{
		
		_new_game_objects.push_front(game_object);
		game_object->_self = _new_game_objects.begin();
	}

	void Scene::GameObjectsManager::Remove(GameObject* game_object)
	{
		_mutex.lock();
		_deleted_game_objects.push_front(game_object);
		_mutex.unlock();
	}

	void Scene::GameObjectsManager::Update()
	{
		for (auto& i : _deleted_game_objects)
		{
			_current_game_objects.erase(i->_self);
			delete i;
		}
		_current_game_objects.splice(_current_game_objects.end(), _new_game_objects);
		for (auto& i : _current_game_objects)
		{
			i->_FramePreprocess();
		}

	}

	void Scene::_ProcessPerThread(size_t thread)
	{
		Event::IUpdate::FrameProcess(thread);
		Event::IRender3D::FrameProcess(thread);
		Event::IRender2D::FrameProcess(thread);
		ExtraX::graphics->FinishCommandList(thread);
	}

	void Scene::_Preprocess()
	{
		_game_objects_manager.Update();

		Event::IUpdate::FramePreprocess();
		Event::IRender3D::FramePreprocess();
		Event::IRender2D::FramePreprocess();
	}

	void Scene::_Process()
	{
		ExtraX::graphics->Begin();
		_thread_manager.SendBeginSignal();
		_thread_manager.WaitCompletionSignal();
		ExtraX::graphics->End();
	}

	void Scene::Start()
	{
		_thread_manager.Start(this, &Scene::_ProcessPerThread);
	}

	void Scene::Run()
	{
		_Preprocess();
		_Process();
	}

	GameObject::ComponentsManager::ComponentsManager(Scene* scene, GameObject* game_object) :
		_scene(scene),
		_game_object(game_object)
	{

	}

	GameObject::ComponentsManager::~ComponentsManager()
	{
		for (auto& i : _new_components)
		{
			delete i;
		}

		for (auto& i : _current_components)
		{
			delete i;
		}
	}

	void GameObject::ComponentsManager::Lock()
	{
		_mutex.lock();
		GameObject::_focus_scene = _scene;
		GameObject::_focus_game_object = _game_object;
	}

	void GameObject::ComponentsManager::Unlock()
	{
		_mutex.unlock();
	}

	void GameObject::ComponentsManager::Add(Component* component)
	{
		
		_new_components.push_front(component);
		component->_self = _new_components.begin();
		_new_components_copy.push_front(component);
	}

	void GameObject::ComponentsManager::Remove(Component* component)
	{
		_mutex.lock();
		_deleted_components.push_front(component);
		_mutex.unlock();
	}

	void GameObject::ComponentsManager::Update()
	{
		for (auto& i : _deleted_components)
		{
			_current_components.erase(i->_self);
			delete i;
		}
		_deleted_components.clear();


		_current_components.splice(_current_components.end(), _new_components);

		for (auto& i : _new_components_copy)
		{
			Event::IOnStart* on_start = dynamic_cast<Event::IOnStart*>(i);
			if (on_start) on_start->OnStart();
		}
		_new_components_copy.clear();
	}

	void GameObject::_FramePreprocess()
	{
		_components_manager.Update();
	}

	void GameObject::Destroy()
	{
		scene->_game_objects_manager.Remove(this);
	}

	std::list<Component*>& Component::GetComponents()
	{
		return game_object->_components_manager._current_components;
	}

	void Component::Destroy()
	{
		game_object->_components_manager.Remove(this);
	}

}