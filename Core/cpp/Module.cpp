#include "Game/Module.h"
#include "Common/Graphics.h"


namespace XX::Game
{
	Scene::GameObjectsManager::GameObjectsManager(Scene* scene):
		scene(scene)
	{

	}

	Scene::GameObjectsManager::~GameObjectsManager()
	{
		for (auto& i : new_game_objects)
		{
			delete i;
		}

		for (auto& i : current_game_objects)
		{
			delete i;
		}
	}

	void Scene::GameObjectsManager::Lock()
	{
		mutex.lock();
		Scene::_focus_scene = scene;
	}

	void Scene::GameObjectsManager::Unlock()
	{
		mutex.unlock();
	}

	void Scene::GameObjectsManager::Add(GameObject* game_object)
	{
		
		new_game_objects.push_front(game_object);
		game_object->_self = new_game_objects.begin();
	}

	void Scene::GameObjectsManager::Remove(GameObject* game_object)
	{
		mutex.lock();
		deleted_game_objects.push_front(game_object);
		mutex.unlock();
	}

	void Scene::GameObjectsManager::Update()
	{
		for (auto& i : deleted_game_objects)
		{
			current_game_objects.erase(i->_self);
			delete i;
		}
		current_game_objects.splice(current_game_objects.end(), new_game_objects);
		for (auto& i : current_game_objects)
		{
			i->_FramePreprocess();
		}

	}

	void Scene::UpdateManager::ProcessPerThread(size_t thread_num)
	{
		auto iter = _events_list.begin();
		auto end = _events_list.end();
		Helper::Next(iter, end, thread_num);
		while (iter != end)
		{
			(*iter)->Update();
			Helper::Next(iter, end, ExtraX::thread_num);
		}
	}

	void Scene::Render2DManager::ProcessPerThread(size_t thread_num)
	{
		auto iter = _events_list.begin();
		auto end = _events_list.end();
		Helper::Next(iter, end, thread_num);
		while (iter != end)
		{
			(*iter)->Render2D(thread_num);
			Helper::Next(iter, end, ExtraX::thread_num);
		}
	}

	void Scene::Render3DManager::ProcessPerThread(size_t thread_num)
	{
		auto iter = _events_list.begin();
		auto end = _events_list.end();
		Helper::Next(iter, end, thread_num);
		while (iter != end)
		{
			(*iter)->Render3D(thread_num);
			Helper::Next(iter, end, ExtraX::thread_num);
		}
	}

	void Scene::_ProcessPerThread(size_t thread_num)
	{
		_update_manager->ProcessPerThread(thread_num);
		_render3d_manager->ProcessPerThread(thread_num);
		_render2d_manager->ProcessPerThread(thread_num);
		ExtraX::graphics->FinishCommandList(thread_num);
	}

	void Scene::_Preprocess()
	{
		_game_objects_manager->Update();

		
	}

	void Scene::_Process()
	{
		ExtraX::graphics->Begin();
		_thread_manager.SendBeginSignal();
		_thread_manager.WaitCompletionSignal();
		ExtraX::graphics->End();
	}

	Scene::~Scene()
	{
		delete _game_objects_manager;
		delete _update_manager;
		delete _render3d_manager;
		delete _render2d_manager;
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

	void GameObject::OnStartManager::OnStart()
	{
		for (auto& i : _events_list)
		{
			i->OnStart();
		}
		_events_list.clear();
	}

	void GameObject::OnTansformManager::OnTansform()
	{
		for (auto& i : _events_list)
		{
			i->OnTransform();
		}
	}

	void GameObject::OnTranslateManager::OnOnTranslate()
	{
		for (auto& i : _events_list)
		{
			i->OnTranslate();
		}
	}

	void GameObject::OnRotateManager::OnRotate()
	{
		for (auto& i : _events_list)
		{
			i->OnRotate();
		}
	}

	void GameObject::OnScaleManager::OnOnScale()
	{
		for (auto& i : _events_list)
		{
			i->OnScale();
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


		for (auto& i : _new_components)
		{
			_scene->_update_manager->Add(i);
			_scene->_render3d_manager->Add(i);
			_scene->_render2d_manager->Add(i);
			_game_object->_onstart_manager->Add(i);
			_game_object->_ontransform_manager->Add(i);
			_game_object->_ontranslate_manager->Add(i);
			_game_object->_onrotate_manager->Add(i);
			_game_object->_onscale_manager->Add(i);
		}


		_current_components.splice(_current_components.end(), _new_components);

		
	}

	void GameObject::_FramePreprocess()
	{
		_components_manager->Update();
		_onstart_manager->OnStart();
	}

	GameObject::~GameObject()
	{
		delete _components_manager;
		delete _onstart_manager;
		delete _ontransform_manager;
		delete _ontranslate_manager;
		delete _onrotate_manager;
		delete _onscale_manager;
	}

	void GameObject::Destroy()
	{
		scene->_game_objects_manager->Remove(this);
	}

	std::list<Component*>& Component::GetComponents()
	{
		return game_object->_components_manager->_current_components;
	}

	void Component::Destroy()
	{
		game_object->_components_manager->Remove(this);
	}


	


	

	


}