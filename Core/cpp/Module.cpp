#include "Game/Module.h"
#include "Game/Event/Event.h"
#include "Common/Graphics.h"


namespace XX::Game
{
	void Scene::_SubProcess(size_t thread)
	{
		//while (true)
		//{
			//_thread_manager.WaitBeginSignal(thread);
			if (!ExtraX::running) return;
			Event::IUpdate::FrameProcess(thread);
			Event::IRender3D::FrameProcess(thread);
			Event::IRender2D::FrameProcess(thread);
			ExtraX::graphics->FinishCommandList(thread);
			//_thread_manager.SendCompletionSignal(thread);
		//}
	}

	Scene::~Scene()
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

	void Scene::FramePreprocess()
	{
		for (auto& i : _deleted_game_objects)
		{
			_current_game_objects.erase(i->_self);
			delete i;
		}
		_deleted_game_objects.clear();

		_current_game_objects.splice(_current_game_objects.end(), _new_game_objects);
		_new_game_objects_copy.clear();

		for (auto& i : _current_game_objects)
		{
			i->_FramePreprocess();
		}

		Event::IUpdate::FramePreprocess();
		Event::IRender3D::FramePreprocess();
		Event::IRender2D::FramePreprocess();
	}

	void Scene::FrameProcess()
	{
		ExtraX::graphics->Begin();
		//_thread_manager.SendBeginSignal();
		//_thread_manager.WaitCompletionSignal();

		for (size_t i = 0; i < THREAD_NUM; ++i)
		{
			_SubProcess(i);
		}

		ExtraX::graphics->End();
	}

	GameObject::~GameObject()
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

	void GameObject::_FramePreprocess()
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

	void GameObject::Destroy()
	{
		scene->_deleted_game_objects.push_front(this);
	}

	std::list<Component*>& Component::GetComponents()
	{
		return game_object->_current_components;
	}

	void Component::Destroy()
	{
		game_object->_deleted_components.push_front(this);
	}
}