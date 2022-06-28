#include "Game/Event/IRender.h"
#include "Common/Graphics.h"
#include "Game/Components/Camera.h"

namespace XX::Game::Event
{
	IRender2D::IRender2D()
	{
		_new_list.push_front(this);
		_self = _new_list.begin();
	}

	IRender2D::~IRender2D()
	{
		_current_list.erase(_self);
	}

	void IRender2D::FramePreprocess()
	{
		_current_list.splice(_current_list.end(), _new_list);
	}

	void IRender2D::FrameProcess(size_t thread)
	{
		auto i = _current_list.begin();
		auto end = _current_list.end();
		Helper::Next(i, end, thread);
		while (i != end)
		{
			(*i)->Render2D(thread);
			Helper::Next(i, end, THREAD_NUM);
		}
	}

	IRender3D::IRender3D()
	{
		_new_list.push_front(this);
		_self = _new_list.begin();
	}

	IRender3D::~IRender3D()
	{
		_current_list.erase(_self);
	}

	void IRender3D::FramePreprocess()
	{
		_current_list.splice(_current_list.end(), _new_list);
	}

	void IRender3D::FrameProcess(size_t thread)
	{
		Components::Camera::Set(thread);
		auto i = _current_list.begin();
		auto end = _current_list.end();
		Helper::Next(i, end, thread);
		while (i != end)
		{
			(*i)->Render3D(thread);
			Helper::Next(i, end, THREAD_NUM);
		}
	}
}