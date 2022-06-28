#include "Game/Event/IUpdate.h"

#include <Windows.h>


namespace XX::Game::Event
{

	IUpdate::IUpdate()
	{
		_new_list.push_front(this);
		_self = _new_list.begin();
	}

	IUpdate::~IUpdate()
	{
		_current_list.erase(_self);
	}

	void IUpdate::FramePreprocess()
	{
		_current_list.splice(_current_list.end(), _new_list);
	}

	void IUpdate::FrameProcess(size_t thread)
	{
		auto i = _current_list.begin();
		auto end = _current_list.end();
		Helper::Next(i, end, thread);
		while (i != end)
		{
			(*i)->Update();
			Helper::Next(i, end, THREAD_NUM);
		}
	}
}